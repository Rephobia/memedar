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


#include "memedar/utils/time.hpp"
#include "memedar/utils/find.hpp"
#include "memedar/utils/storage.hpp"

#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/taskbook.hpp"

#include "memedar/model/service/deck_to_taskbook.hpp"

#include "memedar/model/dal/transaction_guard.hpp"
#include "memedar/model/dal/mapper.hpp"


using md::model::deck_to_taskbook_detail;

void deck_to_taskbook_detail::add_deck(deck::deck&& deck)
{
	m_decks.push_back(std::move(deck));
}

void deck_to_taskbook_detail::delete_deck(deck::deck& deck)
{
	auto deck_it = utils::find_by_id(deck.id(), m_decks);
	if (deck_it != m_decks.end()) {
		m_tasks.erase(deck);
		m_decks.erase(deck_it);
	}	
}

std::deque<md::model::deck::deck>& deck_to_taskbook_detail::get_decks()
{
	return m_decks;
}

deck_to_taskbook_detail::iterator deck_to_taskbook_detail::begin()
{
	return m_tasks.begin();
}

deck_to_taskbook_detail::iterator deck_to_taskbook_detail::end()
{
	return m_tasks.end();
}

deck_to_taskbook_detail::iterator deck_to_taskbook_detail::add_taskbook(deck::deck& deck,
	  task::taskbook&& book)
{
	decltype(auto) pair = std::make_pair(static_cast<identity>(deck), std::move(book));
	return m_tasks.insert(std::move(pair)).first;
}

deck_to_taskbook_detail::iterator deck_to_taskbook_detail::get_taskbook(md::model::deck::deck& deck)
{
	return m_tasks.find(deck);
}


using md::model::deck_to_taskbook;

deck_to_taskbook::deck_to_taskbook(dal::mapper& mapper)
	: m_mapper    {mapper}
{ ;}

md::model::task::taskbook& deck_to_taskbook::get_taskbook(deck::deck& deck)
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	decltype(auto) it {m_storage.get_taskbook(deck)};
	
	if (it == m_storage.end()) {
		
		decltype(auto) book {make_taskbook(deck)};
		it = m_storage.add_taskbook(deck, std::move(book));	
	}
	
	transaction.commit();

	return it->second;
}

std::deque<md::model::deck::deck>& deck_to_taskbook::get_decks()
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	decltype(auto) decks {m_storage.get_decks()};
	
	if (not m_decks_loaded) {
		decks = m_mapper.deck->load_decks();
		m_decks_loaded = true;
	}
	
	transaction.commit();
	
	return decks;
}

void deck_to_taskbook::add_deck(deck::deck&& deck)
{
	m_storage.add_deck(std::move(deck));
}

void deck_to_taskbook::delete_deck(deck::deck& deck)
{
	m_storage.delete_deck(deck);
}

md::model::task::taskbook deck_to_taskbook::make_taskbook(deck::deck& deck)
{
	task::taskbook taskbook {deck};
	
	if (deck.empty()) {
		m_mapper.card->load_cards(deck);
	}
	
	if (not utils::time::is_today(deck.last_opening())) {
		m_mapper.task->delete_done_task(deck);
		m_mapper.deck->reset_daily_limits(deck);
	}

	m_mapper.task->load_taskbook(deck, taskbook);

	fill_from_deck(deck, taskbook);
	m_mapper.deck->update_last_opening(deck);
		
	return taskbook;
}

void deck_to_taskbook::fill_from_deck(deck::deck& deck, task::taskbook& taskbook)
{
	for (auto it = deck.begin(); taskbook.space() and it != deck.end(); it++) {

		if (decltype(auto) task {taskbook.check_card(*it)}) {
			m_mapper.task->save_task(deck, task.value());
			taskbook.add_task(std::move(task.value()));
		}
	}
}
