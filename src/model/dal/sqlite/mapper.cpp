/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov (Linhurdos) <teremdev@gmail.com>

 * This file is part of Memedar (flashcard system)
 * Memedar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include <ctime>
#include <memory>
#include <filesystem>
#include <deque>


#include <sqlite3.h>
#include <QString>

#include "memedar/utils/find.hpp"
#include "memedar/utils/time.hpp"
#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"

#include "memedar/model/dal/mapper.hpp"
#include "memedar/model/dal/transaction.hpp"
#include "memedar/model/dal/card_mapper.hpp"
#include "memedar/model/dal/deck_mapper.hpp"
#include "memedar/model/dal/task_mapper.hpp"
#include "memedar/model/dal/transaction_guard.hpp"

#include "memedar/model/dal/sqlite/adapter.hpp"
#include "memedar/model/dal/sqlite/transaction.hpp"
#include "memedar/model/dal/sqlite/card_mapper.hpp"
#include "memedar/model/dal/sqlite/deck_mapper.hpp"
#include "memedar/model/dal/sqlite/task_mapper.hpp"
#include "memedar/model/dal/sqlite/mapper.hpp"


using md::model::dal::sqlite::mapper;

mapper::~mapper() = default;

mapper::mapper(md::model::dal::sqlite::adapter::handle& db)
	: m_transaction    {std::make_unique<sqlite::transaction>(db)}
	, m_card_mapper    {std::make_unique<sqlite::card_mapper>(db)}
	, m_deck_mapper    {std::make_unique<sqlite::deck_mapper>(db)}
	, m_task_mapper    {std::make_unique<sqlite::task_mapper>(db)}
{
	auto guard {dal::make_transaction(*m_transaction)};

	m_card_mapper->create_table();
	m_deck_mapper->create_table();
	m_task_mapper->create_table();

	guard.commit();
}

md::model::dal::transaction_guard mapper::make_transaction()
{
	return dal::make_transaction(*m_transaction);
}

void mapper::save_card(deck::deck& deck,
                       task::task_book& task_book,
                       card::card_dto&& new_card)
{
	if (deck.empty()) {
		m_card_mapper->load_cards(deck);
	}
		
	decltype(auto) card {m_card_mapper->save_card(deck, std::move(new_card))};

	decltype(auto) shared_card {deck.add_card(std::move(card))};
	
	std::optional<task::task> task {task_book.check_card(shared_card)};
	if (task) {
		m_task_mapper->save_task(deck, task.value());
		task_book.add_task(std::move(task.value()));
	}
}


void mapper::save_deck(std::deque<deck::deck>& decks,
                       deck::deck_value&& deck_value)
{
	decltype(auto) deck {m_deck_mapper->save_deck(std::move(deck_value))};
	decks.push_back(std::move(deck));
}

std::deque<md::model::deck::deck> mapper::load_decks()
{
	return m_deck_mapper->load_decks();
}

md::model::task::task_book mapper::make_task_book(deck::deck& deck)
{
	task::task_book task_book {deck};
	
	if (deck.empty()) {
		m_card_mapper->load_cards(deck);
	}

	if (not utils::time::is_today(deck.last_opening())) {
		m_task_mapper->delete_done_task(deck);
		m_deck_mapper->reset_daily_limits(deck);
	}

	m_task_mapper->load_task_book(deck, task_book);
	fill_from_deck(deck, task_book);
	m_deck_mapper->update_last_opening(deck);
		
	return task_book;
}

void mapper::fill_from_deck(deck::deck& deck, task::task_book& task_book)
{
	for (auto it = deck.begin(); task_book.space() and it != deck.end(); it++) {

		if (decltype(auto) task {task_book.check_card(*it)}) {
			m_task_mapper->save_task(deck, task.value());
			task_book.add_task(std::move(task.value()));
		}
	}
}
void mapper::update_side(side::side& old_side, side::side_value&& new_side)
{
	m_card_mapper->update_side(old_side, new_side);
	old_side = std::move(new_side);
}

void mapper::update_card(md::model::card::card& card, bool typing)
{
	m_card_mapper->update_card(card, typing);
	card.has_typing = typing;
}

void mapper::reset_task(task::task& task)
{
	m_card_mapper->reset_combo(*task.card);
	m_task_mapper->change_state(task, task::state::answering);
}

void mapper::done_noob(deck::deck& deck, task::task& task, std::time_t gap)
{		
	m_deck_mapper->decrement_daily_noob(deck);
	m_card_mapper->update_repeat(*task.card, gap + std::time(nullptr));
	
	m_task_mapper->change_state(task, task::state::done);
	task.card->increment_combo();
	deck.process_card(*task.card);
}

void mapper::done_ready(deck::deck& deck, task::task& task, std::time_t gap)
{
	m_deck_mapper->decrement_daily_ready(deck);
	m_card_mapper->update_repeat(*task.card, gap + task.card->repeat());
	
	m_task_mapper->change_state(task, task::state::done);
	task.card->increment_combo();
	deck.process_card(*task.card);
}
