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


#ifndef MEMEDAR_VIEW_DESIGNER_HPP
#define MEMEDAR_VIEW_DESIGNER_HPP


namespace md::view {
	class designer;
}


class md::view::designer
{
public:
	virtual void show(const md::model::deck::deck& deck,
	                  QString question = QString {},
	                  QString answer = QString {}) = 0;
	virtual void show() = 0;

	boost::signals2::signal<void(std::int64_t deck_id,
	                             md::model::card::card& card)> add_card {};
	boost::signals2::signal<void(md::model::deck::deck& deck)> add_deck {};
	boost::signals2::signal<void()> cancel {};

	virtual ~designer() = default;
};


#endif // MEMEDAR_VIEW_DESIGNER_HPP
