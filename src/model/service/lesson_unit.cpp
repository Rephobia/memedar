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


#include <ctime>
#include <memory>
#include <deque>
#include <map>


#include <QString>


#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/taskbook.hpp"

#include "memedar/model/dal/transaction_guard.hpp"
#include "memedar/model/dal/mapper.hpp"
#include "memedar/model/service/lesson_unit.hpp"


using md::model::lesson_unit;

lesson_unit::lesson_unit(dal::mapper& mapper)
	: m_mapper {mapper}
{ ;}

void lesson_unit::again_task(task::task& task)
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	m_mapper.card->reset_combo(*task.card);
	m_mapper.task->change_state(task, task::state::answering);
	
	transaction.commit();
}

void lesson_unit::done_task(deck::deck& deck, task::task& task, std::time_t gap)
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	task.card->visit(
	                 [this, &deck, &task, &gap](card::noob_t&)
	                 {
		                 gap += std::time(nullptr);		                 
		                 m_mapper.deck->decrement_daily_noob(deck);
	                 },
	                 [this, &deck, &task, &gap](card::ready_t&)
	                 {
		                 gap += task.card->repeat();
		                 m_mapper.deck->decrement_daily_ready(deck);
	                 });
	
	m_mapper.card->update_repeat(*task.card, gap);
	
	m_mapper.task->change_state(task, task::state::done);
	
	task.card->increment_combo();
	
	deck.process_card(*task.card);
		
	transaction.commit();
}
