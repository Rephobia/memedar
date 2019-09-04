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


#include <string>

#include "memedar/model/dal/sqlite/task_mapper_resources.hpp"


using md::model::dal::sqlite::task_index;
namespace res = md::model::dal::sqlite::task_resources;


std::string res::create_table()
{
	std::string cmd {"create table if not exists tasks("
	                 "card_id integer primary key,"
	                 "deck_id integer,"
	                 "state integer,"
	                 "foreign key (card_id) references cards(id) on delete cascade,"
	                 "foreign key (deck_id) references decks(id) on delete cascade);"};
	return cmd;
}

std::string res::insert_cmd()
{
	std::string cmd {"insert into tasks("
	                 "card_id, deck_id, state)"
	                 "values (?1, ?2, ?3);"};

	return cmd;
}

task_index res::insert_index()
{
	task_index ind {};
	ind.set_card_id(1);
	ind.set_deck_id(2);
	ind.set_state(3);
	return ind;
}

std::string res::select_cmd()
{
	std::string cmd {"select * from tasks where deck_id = ?1;"};
	return cmd;
}

task_index res::select_index()
{
	task_index ind {};
	ind.set_card_id(0);
	ind.set_deck_id(1);
	ind.set_state(2);
	return ind;
}

std::string res::change_state_cmd()
{
	std::string cmd {"update tasks set state = ?1 where card_id = ?2;"};
	return cmd;
}

task_index res::change_state_index()
{
	task_index ind {};
	ind.set_state(1);
	ind.set_card_id(2);
	return ind;
}

std::string res::delete_cmd()
{
	std::string cmd {"delete from tasks where tasks.card_id = ?1;"};
	return cmd;
}

task_index res::delete_index()
{
	task_index ind {};
	ind.set_card_id(1);
	return ind;
}

std::string res::delete_done_cmd()
{
	std::string cmd {"delete from tasks where deck_id = ?1 and state = ?2;"};
	return cmd;
}

task_index res::delete_done_index()
{
	task_index ind {};
	ind.set_deck_id(1);
	ind.set_state(2);
	return ind;
}
