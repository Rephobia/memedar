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


#ifndef MEMEDAR_LOBBY_PRESENTER_HPP
#define MEMEDAR_LOBBY_PRESENTER_HPP


namespace md::model::deck {
	class deck;
}

namespace md::model {
	class deck_service;
}


namespace md::view {
	class lobby;
}

namespace md {
	class lobby_presenter;
}

class md::lobby_presenter
{
public:
	lobby_presenter(md::model::deck_service& deck_service,
	                md::view::lobby& lobby);
	void run();
	boost::signals2::signal<void(std::int64_t deck_id)> go_to_lesson {};
	boost::signals2::signal<void(const md::model::deck::deck& deck)> go_to_designer {};
protected:
	md::model::deck_service& m_deck_service;
	md::view::lobby& m_lobby;
};


#endif // MEMEDAR_LOBBY_PRESENTER_HPP
