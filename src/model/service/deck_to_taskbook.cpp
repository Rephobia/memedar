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
#include "memedar/model/task/task_book.hpp"

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
		m_tasks.erase(deck.id());
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
	  task::task_book&& book)
{
	decltype(auto) pair = std::make_pair(deck.id(), std::move(book));
	return m_tasks.insert(std::move(pair)).first;
}

deck_to_taskbook_detail::iterator deck_to_taskbook_detail::get_taskbook(md::model::deck::deck& deck)
{
	return m_tasks.find(deck.id());
}


using md::model::deck_to_taskbook;

deck_to_taskbook::deck_to_taskbook(dal::mapper& mapper)
	: m_mapper    {mapper}
{ ;}

md::model::task::task_book& deck_to_taskbook::get_task_book(deck::deck& deck)
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	decltype(auto) it {m_storage.get_taskbook(deck)};
	
	if (it == m_storage.end()) {
		
		decltype(auto) book {make_task_book(deck)};
		it = m_storage.add_taskbook(deck, std::move(book));	
	}
	
	transaction.commit();

	return it->second;
}

std::deque<md::model::deck::deck>& deck_to_taskbook::get_decks()
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	decltype(auto) decks {m_storage.get_decks()};
	
	if (decks.empty()) {
		decks = m_mapper.deck->load_decks();
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

md::model::task::task_book deck_to_taskbook::make_task_book(deck::deck& deck)
{
	task::task_book task_book {deck};
	
	if (deck.empty()) {
		m_mapper.card->load_cards(deck);
	}
	
	if (not utils::time::is_today(deck.last_opening())) {
		m_mapper.task->delete_done_task(deck);
		m_mapper.deck->reset_daily_limits(deck);
	}

	m_mapper.task->load_task_book(deck, task_book);

	fill_from_deck(deck, task_book);
	m_mapper.deck->update_last_opening(deck);
		
	return task_book;
}

void deck_to_taskbook::fill_from_deck(deck::deck& deck, task::task_book& task_book)
{
	for (auto it = deck.begin(); task_book.space() and it != deck.end(); it++) {

		if (decltype(auto) task {task_book.check_card(*it)}) {
			m_mapper.task->save_task(deck, task.value());
			task_book.add_task(std::move(task.value()));
		}
	}
}
