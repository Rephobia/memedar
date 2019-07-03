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


#ifndef LESSON_PRESENTER_HPP
#define LESSON_PRESENTER_HPP


class QString;

namespace md::model::deck {
	class deck;
}

namespace md::model::task {
	class task_book;
}

namespace md::model {
	class deck_service;
	class task_service;
}

namespace md::view {
	class lesson;
}

namespace md {
	class presenter;
	class lesson_presenter;

}


class md::lesson_presenter : public md::presenter
{
public:
	lesson_presenter(md::controller& controller,
	                 model::deck::deck& deck,
	                 model::deck_service& deck_service,
	                 model::task_service& task_service,
	                 view::lesson& lesson);

	void run() override;
protected:
	void show_answer(const QString& answer);
	void again();
	void done(std::time_t gap);
protected:
	md::controller& m_controller;
	md::model::deck_service& m_deck_service;
	md::model::task_service& m_task_service;
	md::view::lesson& m_lesson;
	md::model::task::task_book& m_task_book;
};


#endif // LESSON_PRESENTER_HPP
