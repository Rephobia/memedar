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
#include <filesystem>

#include <sqlite3.h>
#include <QString>

#include "memedar/utils/storage.hpp"
#include "memedar/utils/find.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"

#include "memedar/model/dal/task_mapper.hpp"
#include "memedar/model/dal/sqlite/adapter.hpp"
#include "memedar/model/dal/sqlite/task_mapper.hpp"
#include "memedar/model/dal/sqlite/task_mapper_resources.hpp"


using md::model::dal::sqlite::task_index;
using md::model::dal::sqlite::task_mapper;
using md::model::dal::sqlite::adapter::binder;
using md::model::dal::sqlite::adapter::connector;
namespace res = md::model::dal::sqlite::task_resources;


task_mapper::task_mapper(adapter::handle& db)
	: m_db {db}
{ ;}

void task_mapper::create_table()
{
	adapter::step(m_db, adapter::prepare_sqlite(m_db, res::create_table()));
}

void task_mapper::save_task(const deck::deck& deck,
                            const task::task& task)
{
	static connector conn {m_db, res::insert_cmd()};
	task_index ind {res::insert_index()};

	conn.exec_bind(binder {ind.card_id(), task.card->id()},
	               binder {ind.deck_id(), deck.id()},
	               binder {ind.state(), static_cast<int>(task.state)});
}

void task_mapper::load_task_book(task::task_book& task_book)
{
	static connector conn {m_db, res::select_cmd()};
	task_index ind {res::select_index()};

	conn.bind(ind.deck_id(), task_book.deck.id());

	while (conn.step() == SQLITE_ROW and task_book.space()) {

		auto card_it {utils::find_by_id(conn.read_int64t(ind.card_id()),
		                                task_book.deck)};

		auto  state {static_cast<task::state>(conn.read_int64t(ind.state()))};
		task_book.add_card(*card_it, state);
	}
}

void task_mapper::change_state(task::task& task, task::state state)
{
	static connector conn {m_db, res::change_state_cmd()};
	task_index ind {res::change_state_index()};

	conn.exec_bind(binder {ind.card_id(), task.id()},
	               binder {ind.state(), static_cast<int>(state)});
	conn.step();
	task.state = state;
}

void task_mapper::delete_done_task(deck::deck& deck)
{
	static connector conn {m_db, res::delete_done_cmd()};
	task_index ind {res::delete_done_index()};

	conn.exec_bind(binder {ind.deck_id(), deck.id()},
	               binder {ind.state(), static_cast<int>(task::state::done)});
}
