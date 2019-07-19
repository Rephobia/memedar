/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov

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


void mapper::save_card(md::model::deck::deck& deck,
                       md::model::card::card&& card)
{
	auto guard {dal::make_transaction(*m_transaction)};
		
	if (deck.empty()) {
		m_card_mapper->load_cards(deck);
	}
		
	m_card_mapper->save_card(deck, std::move(card));
		
	guard.commit();
}


void mapper::save_deck(std::deque<md::model::deck::deck>& decks,
                       md::model::deck::deck&& deck)
{
	auto guard {dal::make_transaction(*m_transaction)};

	m_deck_mapper->save_deck(deck);
	decks.push_back(std::move(deck));
		
	guard.commit();
}

std::deque<md::model::deck::deck> mapper::load_decks()
{
	auto guard {dal::make_transaction(*m_transaction)};
		
	std::deque<deck::deck> decks {m_deck_mapper->load_decks()};

	guard.commit();
		
	return decks;
}

md::model::task::task_book mapper::make_task_book(md::model::deck::deck& deck)
{
	auto guard {dal::make_transaction(*m_transaction)};
		
	md::model::task::task_book task_book {deck};
	
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
	guard.commit();
		
	return task_book;
}

void mapper::fill_from_deck(md::model::deck::deck& deck,
                            md::model::task::task_book& task_book)
{
	for (auto it = deck.begin(); task_book.space() and it != deck.end(); it++) {

		if (task_book.add_card(*it)) {
			m_task_mapper->save_task(deck, task_book.back());
		}
	}
}

void mapper::reset_combo(md::model::card::card& card)
{
	auto guard {dal::make_transaction(*m_transaction)};

	m_card_mapper->reset_combo(card);

	guard.commit();
}

void mapper::done_noob(md::model::deck::deck& deck, md::model::task::task& task,
                       std::time_t gap)
{
	auto guard {dal::make_transaction(*m_transaction)};
		
	m_deck_mapper->decrement_daily_noob(deck);
	m_card_mapper->update_repeat(*task.card, gap + std::time(nullptr));
	
	m_task_mapper->change_state(task, task::state::done);
	task.card->increment_combo();
	deck.process_card(*task.card);
	
	guard.commit();
}

void mapper::done_ready(md::model::deck::deck& deck, md::model::task::task& task,
                        std::time_t gap)
{
	auto guard {dal::make_transaction(*m_transaction)};
		
	m_deck_mapper->decrement_daily_ready(deck);
	m_card_mapper->update_repeat(*task.card, gap + task.card->repeat());
	
	m_task_mapper->change_state(task, task::state::done);
	task.card->increment_combo();
	deck.process_card(*task.card);
	
	guard.commit();
}
