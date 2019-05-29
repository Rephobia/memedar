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

void card_mapper::save_card(deck::deck& deck, card::card&& card)
{
	save_side(card.question);
	save_side(card.answer);

	static connector conn {m_db, res::insert_cmd()};
	card_index ind {res::insert_index()};

	conn.exec_bind(binder {ind.deck_id(), deck.id()},
	               binder {ind.question_id(), card.question.id()},
	               binder {ind.answer_id(), card.answer.id()},
	               binder {ind.added(), card.added()},
	               binder {ind.repeat(), card.repeat()},
	               binder {ind.combo(), card.get_combo()},
	               binder {ind.typing(), card.has_typing()});

	identity id {::sqlite3_last_insert_rowid(m_db.get())};
	card.identity::operator=(id);

	deck.add_card(std::move(card));
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

		bool typing {conn.read_int64t(ind.typing())};

		deck.add_card(card::card
		              {id, schedule, combo, std::move(q), std::move(a), typing});
	}
}

md::model::side::side card_mapper::read_side(adapter::connector& conn,
                                             sqlite::side_index ind)
{
	identity id {conn.read_int64t(ind.id())};
	QString text {conn.read_string(ind.text())};

	return side::side {id, std::move(text)};
}

void card_mapper::save_side(side::side& side)
{
	static adapter::connector conn {m_db, res::insert_side_cmd()};
	side_index ind {res::insert_side_index()};

	conn.exec_bind(binder {ind.text(), side.text()});

	identity id {::sqlite3_last_insert_rowid(m_db.get())};
	side.identity::operator=(id);
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
