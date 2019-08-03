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


#ifndef MEMEDAR_VIEW_LOBBY_HPP
#define MEMEDAR_VIEW_LOBBY_HPP


namespace md::model::deck {
	class deck;
}

namespace md::view {
	class lobby;
}


class md::view::lobby
{
public:
	virtual void show(std::deque<md::model::deck::deck>& decks) = 0;

	boost::signals2::signal<void(md::model::deck::deck&)> call_lesson {};
	boost::signals2::signal<void(md::model::deck::deck&)> add_card {};
	boost::signals2::signal<void(md::model::deck::deck&)> update_deck {};

	virtual ~lobby() = default;
};


#endif // MEMEDAR_VIEW_LOBBY_HPP
