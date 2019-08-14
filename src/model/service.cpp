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
#include <deque>
#include <map>

#include <QString>

#include "memedar/utils/find.hpp"
#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/card/visitor.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"

#include "memedar/model/dal/transaction_guard.hpp"
#include "memedar/model/dal/mapper.hpp"
#include "memedar/model/service.hpp"


using md::model::service;

service::service(dal::mapper& mapper)
       : m_mapper    {mapper}
{ ;}

void service::save_card(deck::deck& deck, card::card_dto&& new_card)

{
	decltype(auto) transaction {m_mapper.make_transaction()};
	
	m_mapper.save_card(deck,
	                   get_task_book(deck),
	                   std::move(new_card));

	transaction.commit();
}

bool service::update_card(card::card& card, card::card_dto&& new_card)
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	bool updated = false;
	
	if (card.question.text() != new_card.question.text()
	    and card.answer.text() != new_card.answer.text()) {
		m_mapper.update_side(card.question, std::move(new_card.question));
		m_mapper.update_side(card.answer, std::move(new_card.answer));
		updated = true;
	}
	else if (card.question.text() != new_card.question.text()) {
		m_mapper.update_side(card.question, std::move(new_card.question));
		updated = true;

	}
	else if (card.answer.text() != new_card.answer.text()) {
		m_mapper.update_side(card.answer, std::move(new_card.answer));
		updated = true;
	}


	if (card.has_typing != new_card.value.has_typing) {
		m_mapper.update_card(card, new_card.value.has_typing);
		updated = true;
	}

	transaction.commit();
	
	return updated;
}

void service::update_task(task::task& task, card::card_dto&& new_card)
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	bool is_card_updated {update_card(*task.card, std::move(new_card))};

	if (is_card_updated) {
		m_mapper.reset_task(task);
	}
	
	transaction.commit();
}

void service::save_deck(deck::deck_value&& deck_value)
{
	decltype(auto) transaction {m_mapper.make_transaction()};
	
	m_mapper.save_deck(m_decks, std::move(deck_value));
	
	transaction.commit();
}

std::deque<md::model::deck::deck>& service::get_decks()
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	if (m_decks.empty()) {
		m_decks = m_mapper.load_decks();
	}
	
	transaction.commit();
	
	return m_decks;
}

void service::update_deck(md::model::deck::deck& deck,
                          md::model::deck::deck_value&& new_deck)
{
	decltype(auto) transaction {m_mapper.make_transaction()};
	
	if (deck.name() != new_deck.name()) {
		m_mapper.update_deck(deck, std::move(new_deck));
	}
	
	transaction.commit();
}

void service::delete_deck(md::model::deck::deck& deck)
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	m_mapper.delete_deck(deck);

	auto deck_it = utils::find_by_id(deck.id(), m_decks);
	if (deck_it != m_decks.end()) {
		m_tasks.erase(deck.id());
		m_decks.erase(deck_it);
	}
	
	transaction.commit();
}

md::model::task::task_book& service::get_task_book(deck::deck& deck)
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	decltype(auto) it {deck_to_taskbook::get_taskbook(deck)};
	
	if (it == deck_to_taskbook::end()) {
		
		decltype(auto) book {m_mapper.make_task_book(deck)};
		it = deck_to_taskbook::add_taskbook(deck, std::move(book));	
	}
	
	transaction.commit();

	return it->second;
}

void service::again_task(task::task& task)
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	m_mapper.reset_task(task);
	
	transaction.commit();
}

void service::done_task(deck::deck& deck, task::task& task, std::time_t gap)
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	task.card->visit(
	                 [this, &deck, &task, &gap](card::noob_t&)
	                 {
		                 m_mapper.done_noob(deck, task, gap);
	                 },
	                 [this, &deck, &task, &gap](card::ready_t&)
	                 {
		                 m_mapper.done_ready(deck, task, gap);
	                 });
	
	transaction.commit();
}
