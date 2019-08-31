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
#include <filesystem>

#include <sqlite3.h>
#include <QString>

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"

#include "memedar/model/dal/card_mapper.hpp"
#include "memedar/model/dal/sqlite/adapter.hpp"
#include "memedar/model/dal/sqlite/card_mapper.hpp"
#include "memedar/model/dal/sqlite/card_mapper_resources.hpp"


using md::model::dal::sqlite::side_index;
using md::model::dal::sqlite::card_index;
using md::model::dal::sqlite::card_mapper;
using md::model::dal::sqlite::adapter::binder;
using md::model::dal::sqlite::adapter::connector;
namespace res = md::model::dal::sqlite::card_resources;


card_mapper::card_mapper(adapter::handle& db)
	: m_db {db}
{ ;}

void card_mapper::create_table()
{
	adapter::step(m_db, adapter::prepare_sqlite(m_db, res::create_side_cmd()));
	adapter::step(m_db, adapter::prepare_sqlite(m_db, res::create_cmd()));
}

void card_mapper::save_card(deck::deck& deck, card::card_dto&& new_card)
{
	decltype(auto) question {save_side(std::move(new_card.question))};
	decltype(auto) answer {save_side(std::move(new_card.answer))};

	static connector conn {m_db, res::insert_cmd()};
	card_index ind {res::insert_index()};

	conn.exec_bind(binder {ind.deck_id(), deck.id()},
	               binder {ind.question_id(), question.id()},
	               binder {ind.answer_id(), answer.id()},
	               binder {ind.added(), new_card.value.added()},
	               binder {ind.repeat(), new_card.value.repeat()},
	               binder {ind.combo(), new_card.value.get_combo()},
	               binder {ind.typing(), new_card.value.has_typing});

	identity id {::sqlite3_last_insert_rowid(m_db.get())};

	deck.add_card(card::card {id, new_card.value, std::move(question), std::move(answer)});
}

void card_mapper::load_cards(deck::deck& deck)
{
	static connector conn {m_db, res::select_cmd()};

	card_index ind {res::select_index()};
	conn.bind(ind.deck_id(), deck.id());
	while (conn.step() == SQLITE_ROW) {

		identity id {conn.read_int64t(ind.id())};

		auto added  {conn.read_int64t(ind.added())};
		auto repeat {conn.read_int64t(ind.repeat())};
		card::schedule schedule {added, repeat};

		card::combo combo {static_cast<int>(conn.read_int64t(ind.combo()))};

		auto q {read_side(conn, ind.question)};
		auto a {read_side(conn, ind.answer)};
		bool typing {static_cast<bool>(conn.read_int64t(ind.typing()))};

		card::card_value card_value {schedule, combo, typing};
		deck.add_card(card::card {id, card_value, std::move(q), std::move(a)});
	}
}

md::model::side::side card_mapper::read_side(adapter::connector& conn,
                                             sqlite::side_index ind)
{
	identity id {conn.read_int64t(ind.id())};
	side::side_value value {conn.read_string(ind.text())};

	return side::side {id, std::move(value)};
}

md::model::side::side card_mapper::save_side(side::side_value&& side_value)
{
	static adapter::connector conn {m_db, res::insert_side_cmd()};
	side_index ind {res::insert_side_index()};

	conn.exec_bind(binder {ind.text(), side_value.text()});

	identity id {::sqlite3_last_insert_rowid(m_db.get())};
	return side::side {id, std::move(side_value)};
}

void card_mapper::delete_side(const md::model::side::side& side) const
{
	static adapter::connector conn {m_db, res::delete_side_cmd()};
	side_index ind {res::delete_side_index()};
	
	conn.exec_bind(binder {ind.id(), side.id()});
}

void card_mapper::delete_card(const md::model::card::card& card)
{
	delete_side(card.question);
	delete_side(card.answer);
	
	static adapter::connector conn {m_db, res::delete_card_cmd()};
	card_index ind {res::delete_card_index()};

	conn.exec_bind(binder {ind.id(), card.id()});	
}

void card_mapper::update_side(const side::side& old_side,
                              const side::side_value& new_side)
{
	static adapter::connector conn {m_db, res::update_side_cmd()};
	side_index ind {res::update_side_index()};

	conn.exec_bind(binder {ind.id(), old_side.id()},
	               binder {ind.text(), new_side.text()});
}

void card_mapper::update_card(const md::model::card::card& card, bool typing)
{
	static adapter::connector conn {m_db, res::update_typing_cmd()};
	card_index ind {res::update_typing_index()};

	conn.exec_bind(binder {ind.id(), card.id()},
	               binder {ind.typing(), typing});
}

void card_mapper::update_repeat(card::card& card, std::time_t repeat)
{
	static connector conn {m_db, res::update_repeat_cmd()};

	card_index ind {res::update_repeat_index()};

	conn.exec_bind(binder {ind.id(), card.id()},
	               binder {ind.repeat(), repeat});
	card.change_repeat(repeat);
}
void card_mapper::reset_combo(card::card& card)
{
	static connector conn {m_db, res::reset_combo_cmd()};
	card_index ind {res::reset_combo_index()};

	conn.exec_bind(binder {ind.id(), card.id()});

	card.reset_combo();
}
