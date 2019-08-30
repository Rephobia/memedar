/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov

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


#include <QString>
#include <sqlite3.h>

#include "memedar/utils/storage.hpp"
#include "memedar/model/deck/storage.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/dal/sqlite/adapter.hpp"

#include "memedar/model/dal/sqlite/deck_mapper_resources.hpp"
#include "memedar/model/dal/deck_generator.hpp"
#include "memedar/model/dal/sqlite/deck_generator.hpp"


namespace res = md::model::dal::sqlite::deck_resources;
using md::model::dal::sqlite::deck_generator;

deck_generator::deck_generator(adapter::connector& connector)
	: m_conn {connector}
	, m_ind  {res::select_index()}
{
	m_conn.bind(m_ind.timestamp(), std::time(nullptr));
}

std::optional<md::model::deck::deck> deck_generator::get_deck()
{
	if (m_conn.step() == SQLITE_ROW) {
		
		identity id {m_conn.read_int64t(m_ind.id())};

		auto added        {m_conn.read_int64t(m_ind.added())};
		auto last_opening {m_conn.read_int64t(m_ind.last_opening())};

		deck::time time {added, last_opening};
		
		auto max_noob    {m_conn.read_int64t(m_ind.max_noob_cards())};
		auto max_ready   {m_conn.read_int64t(m_ind.max_ready_cards())};
		auto daily_noob  {m_conn.read_int64t(m_ind.daily_noob_cards())};
		auto daily_ready {m_conn.read_int64t(m_ind.daily_ready_cards())};
		deck::limit limit {max_noob, max_ready, daily_noob, daily_ready};

		auto g_gap_value {m_conn.read_int64t(m_ind.good_gap())};
		auto g_gap_ratio {static_cast<int>(m_conn.read_int64t(m_ind.good_ratio()))};
		deck::gap g_gap {g_gap_value, g_gap_ratio};

		auto e_gap_value {m_conn.read_int64t(m_ind.easy_gap())};
		auto e_gap_ratio {static_cast<int>(m_conn.read_int64t(m_ind.easy_ratio()))};
		deck::gap e_gap {e_gap_value, e_gap_ratio};

		deck::gaps gaps {g_gap, e_gap};
		
		auto name {m_conn.read_string(m_ind.name())};
		deck::deck_value value {std::move(name), time, limit, gaps};
		
		auto noob    {m_conn.read_int64t(m_ind.noob_cards())};
		auto ready   {m_conn.read_int64t(m_ind.ready_cards())};
		auto delayed {m_conn.read_int64t(m_ind.delayed_cards())};
		deck::accountant acc {noob, ready, delayed};
		
		return deck::deck {id, std::move(value), std::move(acc)};
	}
	
	return std::nullopt;
}
