/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2018 Roman Erdyakov

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

#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/card/visitor.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"

#include "memedar/model/dal/mapper.hpp"
#include "memedar/model/service.hpp"


using md::model::service;

service::service(dal::mapper& mapper)
	: m_mapper    {mapper}
{ ;}

void service::save_card(deck::deck& deck, card::card&& card)
{
	m_mapper.save_card(deck, std::move(card));
}

void service::save_deck(deck::deck&& deck)
{
	m_mapper.save_deck(m_decks, std::move(deck));
}

std::deque<md::model::deck::deck>& service::get_decks()
{
	if (m_decks.empty()) {
		m_decks = m_mapper.load_decks();
	}
	return m_decks;
}

md::model::task::task_book& service::get_task_book(md::model::deck::deck& deck)
{
	decltype(auto) it {m_tasks.find(deck.id())};
	
	if (it == m_tasks.end()) {
		decltype(auto) book {m_mapper.make_task_book(deck)};
		decltype(auto) pair = std::make_pair(deck.id(), std::move(book));
		return m_tasks.insert(std::move(pair)).first->second;
	}
	else {
		return it->second;
	}
}

void service::again_card(task::task& task)
{
	m_mapper.reset_combo(*task.card);
}

class service::done_visitor : public card::visitor
{
public:
	done_visitor(dal::mapper& mapper,
	             deck::deck& deck, task::task& task, std::time_t gap)
		: m_mapper {mapper}
		, m_deck   {deck}
		, m_task   {task}
		, m_gap    {gap}
	{ ;}

	void visit([[maybe_unused]] card::noob_t& ref) override
	{
		m_mapper.done_noob(m_deck, m_task, m_gap);
	}

	void visit([[maybe_unused]] card::ready_t& ref) override
	{
		m_mapper.done_ready(m_deck, m_task, m_gap);
	}

	void visit([[maybe_unused]] card::delayed_t& ref) override
	{ ;}
protected:
	dal::mapper& m_mapper;
	deck::deck& m_deck;
	task::task& m_task;
	std::time_t m_gap;
};

void service::done_card(deck::deck& deck, task::task& task, std::time_t gap)
{
	done_visitor visitor {m_mapper, deck, task, gap};
	task.card->take_visitor(visitor);
}
