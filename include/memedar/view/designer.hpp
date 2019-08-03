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


#ifndef MEMEDAR_VIEW_DESIGNER_HPP
#define MEMEDAR_VIEW_DESIGNER_HPP


namespace md::model::side {
	class side_value;
}

namespace md::model::card {
	class card_value;
	class card;
	class card_dto;
}

namespace md::model::deck {
	class deck_value;
	class deck;
}

namespace md::view {
	class designer;
}


class md::view::designer
{
public:
	virtual void show_card(const md::model::deck::deck& deck) = 0;
	
	virtual void show_card(const md::model::deck::deck& deck,
	                  const md::model::card::card& card) = 0;
		
	virtual void show_deck() = 0;
	virtual void show_deck(const md::model::deck::deck& deck) = 0;

	boost::signals2::signal<void(md::model::card::card_dto& dto)> add_card {};
	boost::signals2::signal<void(md::model::deck::deck_value& deck)> add_deck {};
	boost::signals2::signal<void()> cancel {};

	virtual ~designer() = default;
};


#endif // MEMEDAR_VIEW_DESIGNER_HPP
