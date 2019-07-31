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


#ifndef MEMEDAR_VIEW_QT_LESSON_PAINTER_HPP
#define MEMEDAR_VIEW_QT_LESSON_PAINTER_HPP


namespace md::view::qt {
	class lesson;
	class lesson_painter;
}


class md::view::qt::lesson_painter : public md::view::qt::ui::box
{
public:
	lesson_painter(const md::model::deck::deck& deck,
	               md::view::qt::lesson& lesson);
	void draw(const md::model::task::task& task);
protected:
	md::view::qt::ui::button* get_designer();
	void answering_state(const md::model::card::card& card);
	void marking_state(const md::model::task::task& task);
	void done_state(const md::model::card::card& card);
protected:
	const md::model::deck::deck& m_deck;
	md::view::qt::lesson& m_lesson;
};


#endif // MEMEDAR_VIEW_QT_LESSON_PAINTER_HPP
