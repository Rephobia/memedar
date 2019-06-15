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


#ifndef MEMEDAR_VIEW_LESSON_HPP
#define MEMEDAR_VIEW_LESSON_HPP


namespace md::view {
	class lesson;
}


class md::view::lesson
{
public:
	virtual void show() = 0;
	virtual void show(const md::model::task::task& task,
	                  const md::model::deck::deck& deck) = 0;

	boost::signals2::signal<void()> prev_task {};
	boost::signals2::signal<void()> next_task {};

	boost::signals2::signal<void(const md::model::task::task& task)> redraw {};
	boost::signals2::signal<void()> answer {};
	boost::signals2::signal<void(const QString& answer)> answer_text {};
	boost::signals2::signal<void()> again {};
	boost::signals2::signal<void(std::time_t gap)> done {};

	boost::signals2::signal<void()> call_designer {};
	virtual ~lesson() = default;
};


#endif // MEMEDAR_VIEW_LESSON_HPP
