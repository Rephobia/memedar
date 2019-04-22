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


#include <string>

#include "memedar/model/dal/sqlite/card_mapper_resources.hpp"


using md::model::dal::sqlite::side_index;
using md::model::dal::sqlite::card_index;

namespace res = md::model::dal::sqlite::card_resources;

std::string res::create_cmd()
{
	std::string cmd {"create table if not exists cards("
	                 "id integer primary key asc,"
	                 "deck_id integer,"
	                 "added integer,"
	                 "repeat integer,"
	                 "combo integer,"
	                 "question_id integer,"
	                 "answer_id integer,"
	                 "typing integer,"
	                 "foreign key (deck_id) references decks(id),"
	                 "foreign key (question_id) references sides(id),"
	                 "foreign key (answer_id) references sides(id));"};
	return cmd;
}

std::string res::create_side_cmd()
{
	std::string cmd {"create table if not exists sides("
	                 "id integer primary key asc,"
	                 "text text"
	                 ");"};
	return cmd;
}

std::string res::insert_cmd()
{
	std::string cmd {"insert into cards("
	                 "deck_id, added, repeat, combo,"
	                 "question_id, answer_id, typing)"
	                 "values (?1, ?2, ?3, ?4, ?5, ?6, ?7);"};
	return cmd;
}

card_index res::insert_index()
{
	card_index ind {};
	ind.set_deck_id(1);
	ind.set_added(2);
	ind.set_repeat(3);
	ind.set_combo(4);
	ind.set_question_id(5);
	ind.set_answer_id(6);
	ind.set_typing(7);
	return ind;
}

std::string res::select_cmd()
{
	std::string cmd {"select * from cards as 'c'"
	                 "left join sides as 's1' on (s1.id = c.question_id)"
	                 "left join sides as 's2' on (s2.id = c.answer_id) "
	                 "where c.deck_id = ?"};
	return cmd;
}

card_index res::select_index()
{
	card_index card {};
	card.set_id(0);
	card.set_deck_id(1);
	card.set_added(2);
	card.set_repeat(3);
	card.set_combo(4);
	card.set_question_id(5);
	card.set_answer_id(6);
	card.set_typing(7);

	card.question.set_id(8);
	card.question.set_text(9);

	card.answer.set_id(10);
	card.answer.set_text(11);

	return card;
}

std::string res::insert_side_cmd()
{
	std::string cmd {"insert into sides(text) values (?1);"};
	return cmd;
}

side_index res::insert_side_index()
{
	side_index ind {};
	ind.set_text(1);
	return ind;
}

std::string res::update_repeat_cmd()
{
	std::string cmd {"update cards set repeat = ?1, combo = combo + 1 "
	                 "where id = ?2;"};
	return cmd;
}

card_index res::update_repeat_index()
{
	card_index ind {};
	ind.set_repeat(1);
	ind.set_id(2);
	return ind;
}

std::string res::reset_combo_cmd()
{
	std::string cmd {"update cards set combo = 1 where id = ?1;"};
	return cmd;
}

card_index res::reset_combo_index()
{
	card_index ind {};
	ind.set_id(1);
	return ind;
}
