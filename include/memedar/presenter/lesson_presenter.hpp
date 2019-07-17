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


#ifndef MEMEDAR_LESSON_PRESENTER_HPP
#define MEMEDAR_LESSON_PRESENTER_HPP


class QString;

namespace md::model::deck {
	class deck;
}

namespace md::model::task {
	class task_book;
}

namespace md::model {
	class service;
}

namespace md::view {
	class error_delegate;
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
	                 md::model::service& service,
	                 md::view::error_delegate& error_delegate,
	                 md::view::lesson& lesson,
	                 md::model::deck::deck& deck);

	void run() override;
protected:
	void show_answer(const QString& answer);
	void again();
	void done(std::time_t gap);
protected:
	md::controller& m_controller;
	md::model::service& m_service;
	md::view::error_delegate& m_error_delegate;
	md::view::lesson& m_lesson;
protected:
	md::model::deck::deck& m_deck;
	md::model::task::task_book& m_task_book;
};


#endif // MEMEDAR_LESSON_PRESENTER_HPP
