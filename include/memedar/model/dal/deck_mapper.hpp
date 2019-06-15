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


#ifndef MEMEDAR_MODEL_DAL_DECK_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_DECK_MAPPER_HPP


namespace md::model::deck {
	class deck;
}

namespace md::model::dal {
	class deck_mapper;
}


class md::model::dal::deck_mapper
{
public:
	virtual void create_table() = 0;

	virtual md::utils::storage<md::model::deck::deck> load_decks() = 0;
	virtual void save_deck(md::model::deck::deck& deck) = 0;

	virtual	void decrement_daily_noob(md::model::deck::deck& deck) = 0;
	virtual	void decrement_daily_ready(md::model::deck::deck& deck) = 0;
	virtual void update_last_opening(md::model::deck::deck& deck) = 0;
	virtual void reset_daily_limits(md::model::deck::deck& deck) = 0;

	virtual ~deck_mapper() = default;
};


#endif // MEMEDAR_MODEL_DAL_DECK_MAPPER_HPP
