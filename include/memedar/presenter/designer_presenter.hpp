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


#ifndef MEMEDAR_DESIGNER_PRESENTER_HPP
#define MEMEDAR_DESIGNER_PRESENTER_HPP


namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
}
namespace md::model {
	class card_service;
	class deck_service;
}

namespace md::view {
	class error_delegate;
	class designer;
}

namespace md {
	class designer_presenter;
}


class md::designer_presenter
{
public:
	designer_presenter(md::model::deck_service& deck_service,
	                   md::model::card_service& card_service,
	                   md::view::error_delegate& error_delegate,
	                   md::view::designer& designer);

	boost::signals2::signal<void()> cancel {};

	void run(const md::model::deck::deck& deck);
	void run();
protected:
	void add_card(std::int64_t deck_id, md::model::card::card&& card);
	void add_deck(md::model::deck::deck&& deck);
protected:
	md::model::deck_service& m_deck_service;
	md::model::card_service& m_card_service;
	md::view::error_delegate& m_error_delegate;
	md::view::designer& m_designer;
};


#endif // MEMEDAR_DESIGNER_PRESENTER_HPP
