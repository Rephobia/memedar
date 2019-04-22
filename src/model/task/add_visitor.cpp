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

#include <QString>

#include "memedar/utils/storage.hpp"
#include "memedar/utils/ref_wrapper.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/card/visitor.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"
#include "memedar/model/task/add_visitor.hpp"


using md::model::task::task_book;
using md::model::task::add_visitor;

add_visitor::add_visitor(task_book& task_book, md::model::card::card& card,
                         md::model::task::state state)
	: m_task_status {false}
	, m_task_book   {task_book}
	, m_card        {card}
	, m_state       {state}
{ ;}

void add_visitor::visit([[maybe_unused]] md::model::card::noob_t& ref)
{
	if (m_task_book.m_noob_space) {
		m_task_book.add(task {m_card, m_state});
		--m_task_book.m_noob_space;
		m_task_status = true;
	}
}

void add_visitor::visit([[maybe_unused]] md::model::card::ready_t& ref)
{
	if (m_task_book.m_ready_space) {
		m_task_book.add(task {m_card, m_state});
		--m_task_book.m_ready_space;
		m_task_status = true;
	}
}

void add_visitor::visit([[maybe_unused]] md::model::card::delayed_t& ref)
{
	m_task_status = false;
}

bool add_visitor::is_task() const
{
	return m_task_status;
}
