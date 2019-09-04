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


#include "memedar/utils/time.hpp"
#include "memedar/utils/find.hpp"

#include "memedar/model/card/card.hpp"
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
	auto deck_it {utils::find_by_id(deck.id(), m_decks)};
	if (deck_it != m_decks.end()) {
		m_tasks.erase(deck);
		m_decks.erase(deck_it);
	}	
}

void deck_to_taskbook_detail::delete_card(deck::deck& deck, card::card& card)
{
	decltype(auto) taskbook {get_taskbook(deck)};

	if (taskbook != m_tasks.end()) {
		taskbook->second.delete_task(card);
	}
	deck.delete_card(card);
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
		
		it = m_storage.add_taskbook(deck, make_taskbook(deck));
		auto& taskbook {it->second};
		deck.card_added.connect([this, &taskbook](md::model::deck::deck& deck,
		                                          std::shared_ptr<md::model::card::card> card)
		                        {
			                        decltype(auto) transaction {m_mapper.make_transaction()};

			                        std::optional<task::task> task {taskbook.check_card(card)};
			                        
			                        if (task) {
				                        m_mapper.task->save_task(deck, task.value());
				                        taskbook.add_task(std::move(task.value()));
			                        }
			                        
			                        transaction.commit();
		                        });
	}
	
	transaction.commit();

	return it->second;
}

std::deque<md::model::deck::deck>& deck_to_taskbook::get_decks()
{
	decltype(auto) decks {m_storage.get_decks()};
	
	if (not m_decks_loaded) {
		decks = load_decks();
	}
	
	return decks;
}

std::deque<md::model::deck::deck> deck_to_taskbook::load_decks()
{
	decltype(auto) transaction {m_mapper.make_transaction()};
	
	std::deque<md::model::deck::deck> decks {};
	
	decltype(auto) generator {m_mapper.deck->get_generator()};
	
	while (std::optional<deck::deck> deck_opt {generator->get_deck()}) {

		deck::deck& deck {deck_opt.value()};
		deck.need_cards.connect([this](deck::deck& deck)
		                       {
			                       decltype(auto) transaction {m_mapper.make_transaction()};
			                       decltype(auto) boss {deck.get_storage_boss()};
			                       
			                       m_mapper.card->load_cards(deck);
			                       
			                       boss.commit();
			                       transaction.commit();
		                       });
		
		decks.push_back(std::move(deck));
	}
		
	m_decks_loaded = true;
	
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

void deck_to_taskbook::delete_card(md::model::deck::deck& deck, md::model::card::card& card)
{
	m_storage.delete_card(deck, card);
}

md::model::task::taskbook deck_to_taskbook::make_taskbook(deck::deck& deck)
{
	task::taskbook taskbook {deck};

	if (not utils::time::is_today(deck.last_opening())) {
		m_mapper.task->delete_done_task(deck);
		m_mapper.deck->reset_daily_limits(deck);
	}

	m_mapper.task->load_taskbook(deck, taskbook);

	fill_from_deck(deck, taskbook);
	m_mapper.deck->update_last_opening(deck);
	
	return taskbook;
}

std::optional<md::model::task::task*> deck_to_taskbook::get_task(deck::deck& deck,
                                                                 card::card& card)
{
	decltype(auto) taskbook {m_storage.get_taskbook(deck)};
	
	if (taskbook == m_storage.end()) {
		return std::nullopt;
	}

	decltype(auto) task {utils::find_by_id(card.id(), taskbook->second)};

	if (task == taskbook->second.end()) {
		return std::nullopt;
	}
		
	return &*task;
}


void deck_to_taskbook::fill_from_deck(deck::deck& deck, task::taskbook& taskbook)
{
	decltype(auto) cards {deck.cards()};
	for (auto it = cards.begin(); taskbook.space() and it != cards.end(); it++) {

		if (decltype(auto) task {taskbook.check_card(*it)}) {
			m_mapper.task->save_task(deck, task.value());
			taskbook.add_task(std::move(task.value()));
		}
	}
}
