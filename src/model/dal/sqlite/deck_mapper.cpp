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
#include <deque>

#include <sqlite3.h>
#include <QString>

#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"

#include "memedar/model/dal/deck_mapper.hpp"
#include "memedar/model/dal/sqlite/adapter.hpp"
#include "memedar/model/dal/sqlite/deck_mapper.hpp"
#include "memedar/model/dal/sqlite/deck_mapper_resources.hpp"


using md::model::dal::sqlite::deck_index;
using md::model::dal::sqlite::deck_mapper;
using md::model::dal::sqlite::adapter::binder;
using md::model::dal::sqlite::adapter::connector;
namespace res = md::model::dal::sqlite::deck_resources;

deck_mapper::deck_mapper(adapter::handle& db)
	: m_db {db}
{ ;}

void deck_mapper::create_table()
{
	adapter::step(m_db, adapter::prepare_sqlite(m_db, res::create_cmd()));
}

md::model::deck::deck deck_mapper::save_deck(deck::deck_value&& deck_value)
{
	static connector conn {m_db, res::insert_cmd()};
	deck_index ind {res::insert_index()};

	auto good_gap {deck_value.good_gap()};
	auto easy_gap {deck_value.easy_gap()};
	conn.exec_bind(binder {ind.name(), deck_value.name()},
	               binder {ind.added(), deck_value.added()},
	               binder {ind.last_opening(), deck_value.last_opening()},
	               binder {ind.max_noob_cards(), deck_value.max_noob_cards()},
	               binder {ind.max_ready_cards(), deck_value.max_ready_cards()},
	               binder {ind.daily_noob_cards(), deck_value.daily_noob_cards()},
	               binder {ind.daily_ready_cards(), deck_value.daily_ready_cards()},
	               binder {ind.good_gap(), good_gap.netto_value()},
	               binder {ind.good_ratio(), good_gap.ratio()},
	               binder {ind.easy_gap(), easy_gap.netto_value()},
	               binder {ind.easy_ratio(), easy_gap.ratio()}
	               );

	identity id {::sqlite3_last_insert_rowid(m_db.get())};
	return deck::deck {id, std::move(deck_value)};
}

std::deque<md::model::deck::deck> deck_mapper::load_decks()
{
	static connector conn {m_db, res::select_cmd()};
	deck_index ind {res::select_index()};

	conn.bind(ind.timestamp(), std::time(nullptr));

	std::deque<md::model::deck::deck> decks {};
	while (conn.step() == SQLITE_ROW) {

		identity id {conn.read_int64t(ind.id())};

		auto added        {conn.read_int64t(ind.added())};
		auto last_opening {conn.read_int64t(ind.last_opening())};

		deck::time time {added, last_opening};
		
		auto max_noob    {conn.read_int64t(ind.max_noob_cards())};
		auto max_ready   {conn.read_int64t(ind.max_ready_cards())};
		auto daily_noob  {conn.read_int64t(ind.daily_noob_cards())};
		auto daily_ready {conn.read_int64t(ind.daily_ready_cards())};
		deck::limit limit {max_noob, max_ready, daily_noob, daily_ready};

		auto g_gap_value {conn.read_int64t(ind.good_gap())};
		auto g_gap_ratio {static_cast<int>(conn.read_int64t(ind.good_ratio()))};
		deck::gap g_gap {g_gap_value, g_gap_ratio};

		auto e_gap_value {conn.read_int64t(ind.easy_gap())};
		auto e_gap_ratio {static_cast<int>(conn.read_int64t(ind.easy_ratio()))};
		deck::gap e_gap {e_gap_value, e_gap_ratio};

		deck::gaps gaps {g_gap, e_gap};
		
		auto name {conn.read_string(ind.name())};
		deck::deck_value value {std::move(name), time, limit, gaps};
		
		auto noob    {conn.read_int64t(ind.noob_cards())};
		auto ready   {conn.read_int64t(ind.ready_cards())};
		auto delayed {conn.read_int64t(ind.delayed_cards())};
		deck::accountant acc {noob, ready, delayed};
		
		decks.push_back(deck::deck {id, std::move(value), std::move(acc)});
	}
	
	return decks;
}

void deck_mapper::decrement_daily_noob(deck::deck& deck)
{
	static connector conn {m_db, res::decrement_daily_noob_cmd()};
	deck_index ind {res::decrement_daily_index()};

	conn.exec_bind(binder {ind.id(), deck.id()});

	deck.decrement_daily_noob();
}

void deck_mapper::decrement_daily_ready(deck::deck& deck)
{
	static connector conn {m_db, res::decrement_daily_ready_cmd()};
	deck_index ind {res::decrement_daily_index()};

	conn.exec_bind(binder {ind.id(), deck.id()});

	deck.decrement_daily_ready();
}

void deck_mapper::update_last_opening(deck::deck& deck)
{
	static connector conn {m_db, res::update_opening_cmd()};
	deck_index ind {res::update_opening_index()};

	auto timestamp {std::time(nullptr)};

	conn.exec_bind(binder {ind.last_opening(), timestamp},
	               binder {ind.id(), deck.id()});

	deck.change_last_opening(timestamp);
}

void deck_mapper::reset_daily_limits(deck::deck& deck)
{
	static connector conn {m_db, res::reset_daily_limits_cmd()};
	deck_index ind {res::reset_daily_limits_index()};

	conn.exec_bind(binder {ind.daily_noob_cards(), deck.max_noob_cards()},
	               binder {ind.daily_ready_cards(), deck.max_ready_cards()},
	               binder {ind.id(), deck.id()});
	deck.reset_daily_limits();
}
