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
	class error_delegate;
}

namespace md::view {
	class lesson;
}

namespace md {
	class lesson_presenter;

}

class md::lesson_presenter
{
public:
	lesson_presenter(md::model::deck_service& deck_service,
	                 md::model::task_service& task_service,
	                 md::view::error_delegate& error_delegate,
	                 md::view::lesson& lesson);

	void run(std::int64_t deck_id);
	
	boost::signals2::signal<void(md::model::deck::deck& deck,
	                             std::function<void()> quit)> go_to_designer {};
	
	~lesson_presenter();
protected:
	void run_current();
	void show_answer();
	void show_answer(const QString& answer);
	void again();
	void done(std::time_t gap);
protected:
	md::model::deck_service& m_deck_service;
	md::model::task_service& m_task_service;
	md::view::error_delegate& m_error_delegate;
	md::view::lesson& m_lesson;

	std::unique_ptr<md::model::task::task_book> m_task_book;
};


#endif // LESSON_PRESENTER_HPP
