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

#include <QString>

#include "memedar/utils/storage.hpp"
#include "memedar/utils/find.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"
#include "memedar/model/card/visitor.hpp"
#include "memedar/model/task/add_visitor.hpp"


using md::model::task::task_book;

task_book::task_book(deck::deck& deck)
	: m_noob_space    {deck.daily_noob_cards()}
	, m_ready_space   {deck.daily_ready_cards()}
	, m_current_index {0}
{ ;}

bool task_book::add_card(std::shared_ptr<md::model::card::card> card) 
{
	add_visitor visitor {*this, task {card, state::answering}};

	if (utils::find_by_id(card->id(), *this) == storage::end()) {
		card->take_visitor(visitor);
	}
	return visitor.is_task();
}

void task_book::add_card(std::shared_ptr<md::model::card::card> card,
                         md::model::task::state state)
{
	add_visitor visitor {*this, task {card, state}};

	card->take_visitor(visitor);
}

std::int64_t task_book::noob_space() const
{
	return m_noob_space;
}

std::int64_t task_book::ready_space() const
{
	return m_ready_space;
}

std::int64_t task_book::space() const
{
	return noob_space() + ready_space();
}

md::model::task::task& task_book::current_task()
{
	return storage::index(m_current_index);
}

md::model::task::task& task_book::prev_task()
{
	return m_current_index > 0
		? storage::index(--m_current_index)
		: storage::index(m_current_index);
}

md::model::task::task& task_book::next_task()
{
	return m_current_index < storage::size() - 1
		? storage::index(++m_current_index)
		: storage::index(m_current_index);
}

void task_book::push_back_current()
{
	decltype(auto) current_it = storage::begin() + m_current_index;
	std::rotate(current_it, current_it + 1, storage::end());
}
