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


#ifndef MEMEDAR_MODEL_DAL_CARD_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_CARD_MAPPER_HPP


namespace md::model::side {
	class side;
	class side_value;
}

namespace md::model::card {
	class card_dto;
	class card;
}

namespace md::model::deck {
	class deck;
	class deck;
}

namespace md::model::dal {
	class card_mapper;
}


class md::model::dal::card_mapper
{
public:
	virtual void create_table() = 0;

	virtual void save_card(md::model::deck::deck& deck,
	                       md::model::card::card_dto&& new_card) = 0;
	
	virtual void load_cards(md::model::deck::deck& deck) = 0;

	virtual void update_side(const md::model::side::side& old_side,
	                         const md::model::side::side_value& new_side) = 0;
	
	virtual void update_card(const md::model::card::card& card, bool typing) = 0;
	
	virtual void delete_card(const md::model::card::card& card) = 0;	
	virtual void update_repeat(md::model::card::card& card, std::time_t repeat) = 0;
	virtual void reset_combo(md::model::card::card& card) = 0;

	virtual ~card_mapper() = default;
};


#endif // MEMEDAR_MODEL_DAL_CARD_MAPPER_HPP
