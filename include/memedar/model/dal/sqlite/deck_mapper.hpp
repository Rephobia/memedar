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


#ifndef MEMEDAR_MODEL_DAL_SQLITE_DECK_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_SQLITE_DECK_MAPPER_HPP


namespace md::model::deck {
	class deck;
}

namespace md::model::dal::sqlite {
	class deck_mapper;
}


class md::model::dal::sqlite::deck_mapper : public md::model::dal::deck_mapper
{
public:
	explicit deck_mapper(md::model::dal::sqlite::adapter::handle& db);

	void create_table() override;

	md::model::deck::deck save_deck(md::model::deck::deck_value&& deck_value) override;
	std::deque<md::model::deck::deck> load_decks() override;
	void update_deck(const md::model::deck::deck& deck,
	                 const md::model::deck::deck_value& new_deck) override;
	
	void decrement_daily_noob(md::model::deck::deck& deck) override;
	void decrement_daily_ready(md::model::deck::deck& deck) override;
	void reset_daily_limits(md::model::deck::deck& deck) override;
	void update_last_opening(md::model::deck::deck& deck) override;
protected:
	md::model::dal::sqlite::adapter::handle& m_db;
};


#endif // MEMEDAR_MODEL_DAL_SQLITE_DECK_MAPPER_HPP
