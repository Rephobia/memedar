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
#include "memedar/utils/find.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/taskbook.hpp"


using md::model::task::task;
using md::model::task::state;
using md::model::task::taskbook;


taskbook::taskbook(deck::deck& deck)
	: m_noob_space    {deck.daily_noob_cards()}
	, m_ready_space   {deck.daily_ready_cards()}
	, m_current_index {0}
{ ;}

std::optional<task>
taskbook::check_card(std::shared_ptr<card::card> card, state state)
{
	std::optional<task> opt_task {std::nullopt};
	if (md::utils::find_by_id(card->id(), *this) == storage::end()) {

		card->visit(
		            [this, card, &opt_task, state](card::noob_t&)
		            {
			            if (m_noob_space) {
				            opt_task = task {card, state};
			            }
		            },
		            [this, card, &opt_task, state](card::ready_t&)
		            {
			            if (m_ready_space) {
				            opt_task = task {card, state};
			            }
		            });
	}

	return opt_task;
}

void taskbook::add_task(task&& task)
{
	task.card->visit([this](card::noob_t&) { m_noob_space--; },
	                 [this](card::ready_t&) { m_ready_space--; });
	storage::add(std::move(task));
}

std::int64_t taskbook::noob_space() const
{
	return m_noob_space;
}

std::int64_t taskbook::ready_space() const
{
	return m_ready_space;
}

std::int64_t taskbook::space() const
{
	return noob_space() + ready_space();
}

md::model::task::task& taskbook::current_task()
{
	return storage::index(m_current_index);
}

md::model::task::task& taskbook::prev_task()
{
	return m_current_index > 0
		? storage::index(--m_current_index)
		: storage::index(m_current_index);
}

md::model::task::task& taskbook::next_task()
{
	return m_current_index < storage::size() - 1
		? storage::index(++m_current_index)
		: storage::index(m_current_index);
}

void taskbook::push_back_current()
{
	decltype(auto) current_it = storage::begin() + m_current_index;
	std::rotate(current_it, current_it + 1, storage::end());
}
