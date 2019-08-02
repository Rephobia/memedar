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


#ifndef MEMEDAR_MODEL_DAL_SQLITE_CARD_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_SQLITE_CARD_MAPPER_HPP


namespace md::model::side {
	class side;
}

namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
}

namespace md::model::dal::sqlite {
	class side_index;
	class card_mapper;
}


class md::model::dal::sqlite::card_mapper : public md::model::dal::card_mapper
{
public:
	explicit card_mapper(md::model::dal::sqlite::adapter::handle& db);

	void create_table() override;

	md::model::card::card save_card(const md::model::deck::deck& deck,
	                                md::model::card::card_dto&& new_card) override;
	void load_cards(md::model::deck::deck& deck) override;

	void update_side(const md::model::side::side& old_side,
	                 const md::model::side::side_value& new_side) override;
	
	void update_card(const md::model::card::card& card, bool typing) override;
	
	void update_repeat(md::model::card::card& card, std::time_t repeat) override;
	void reset_combo(md::model::card::card& card) override;
protected:
	md::model::side::side save_side(md::model::side::side_value&& side_value);
	md::model::side::side read_side(md::model::dal::sqlite::adapter::connector& conn,
	                                md::model::dal::sqlite::side_index ind);
protected:
	md::model::dal::sqlite::adapter::handle& m_db;
};


#endif // MEMEDAR_MODEL_DAL_SQLITE_CARD_MAPPER_HPP
