/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2018 Roman Erdyakov (Linhurdos) <teremdev@gmail.com>

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
#include <map>

#include <QString>

#include "memedar/utils/time.hpp"
#include "memedar/utils/storage.hpp"
#include "memedar/utils/ref_wrapper.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/visitor.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"

#include "memedar/model/dal/transaction.hpp"
#include "memedar/model/dal/card_mapper.hpp"
#include "memedar/model/dal/deck_mapper.hpp"
#include "memedar/model/dal/task_mapper.hpp"
#include "memedar/model/dal/transaction_guard.hpp"

#include "memedar/view/error_delegate.hpp"
#include "memedar/model/task_service.hpp"


using md::model::task_service;

task_service::task_service(md::view::error_delegate& error_delegate,
                           dal::transaction& transaction,
                           dal::card_mapper& card_mapper,
                           dal::deck_mapper& deck_mapper,
                           dal::task_mapper& task_mapper)
	: m_error_delegate {error_delegate}
	, m_transaction    {transaction}
	, m_card_mapper    {card_mapper}
	, m_deck_mapper    {deck_mapper}
	, m_task_mapper    {task_mapper}
{
	try {
		auto guard {dal::make_transaction(m_transaction)};

		m_card_mapper.create_table();
		m_deck_mapper.create_table();
		m_task_mapper.create_table();

		guard.commit();
	}
	catch (std::system_error &e) {
		m_error_delegate.show_error(e);
	}
}

md::model::task::task_book& task_service::get_task_book(md::model::deck::deck& deck)
{
	decltype(auto) it {m_tasks.find(deck.id())};
	
	if (it == m_tasks.end()) {

		decltype(auto) pair = std::make_pair(deck.id(), make_task_book(deck));
		return m_tasks.insert(std::move(pair)).first->second;
		
	}
	else {
		return it->second;
	}
}

md::model::task::task_book task_service::make_task_book(deck::deck& deck)
{
	md::model::task::task_book task_book {deck};
	try {
		auto guard {dal::make_transaction(m_transaction)};

		if (deck.empty()) {
			m_card_mapper.load_cards(deck);
		}

		if (not utils::time::is_today(deck.last_opening())) {
			m_task_mapper.delete_done_task(deck);
			m_deck_mapper.reset_daily_limits(deck);
		}

		m_task_mapper.load_task_book(task_book);
		fill_from_deck(task_book);
		m_deck_mapper.update_last_opening(deck);

		guard.commit();
	}
	catch (std::system_error &e) {

		m_error_delegate.show_error(e);

	}

	return task_book;
}

void task_service::fill_from_deck(md::model::task::task_book& task_book)
{
	decltype(auto) deck {task_book.deck};
	for (auto it = deck.begin(); task_book.space() and it != deck.end(); it++) {

		if (task_book.add_card(*it)) {
			m_task_mapper.save_task(deck, task_book.back());
		}
	}
}

void task_service::again_card(task::task& task)
{
	try {
		auto guard {dal::make_transaction(m_transaction)};

		m_card_mapper.reset_combo(*task.card);

		guard.commit();
	}
	catch (std::system_error &e) {

		m_error_delegate.show_error(e);

	}
}


class task_service::done_visitor : public card::visitor
{
public:
	done_visitor(dal::card_mapper& card_mapper,
	             dal::deck_mapper& deck_mapper,
	             deck::deck& deck, task::task& task, std::time_t gap)
		: m_card_mapper {card_mapper}
		, m_deck_mapper {deck_mapper}
		, m_deck        {deck}
		, m_task        {task}
		, m_gap         {gap}
	{ ;}

	void visit([[maybe_unused]] card::noob_t& ref) override
	{
		m_deck_mapper.decrement_daily_noob(m_deck);
		m_card_mapper.update_repeat(*m_task.card,
		                            m_gap + std::time(nullptr));
	}

	void visit([[maybe_unused]] card::ready_t& ref) override
	{
		m_deck_mapper.decrement_daily_ready(m_deck);
		m_card_mapper.update_repeat(*m_task.card,
		                            m_gap + m_task.card->repeat());
	}

	void visit([[maybe_unused]] card::delayed_t& ref) override
	{
		;
	}
protected:
	dal::card_mapper& m_card_mapper;
	dal::deck_mapper& m_deck_mapper;
	deck::deck& m_deck;
	task::task& m_task;
	std::time_t m_gap;
};


void task_service::done_card(deck::deck& deck, task::task& task, std::time_t gap)
{
	try {
		auto guard {dal::make_transaction(m_transaction)};

		done_visitor visitor {m_card_mapper, m_deck_mapper,
		                      deck, task, gap};
		task.card->take_visitor(visitor);
		deck.process_card(*task.card);
		m_task_mapper.change_state(task, task::state::done);
		task.card->increment_combo();

		guard.commit();
	}
	catch (std::system_error &e) {
		m_error_delegate.show_error(e);
	}
}
