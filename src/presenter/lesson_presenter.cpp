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


#include <ctime>
#include <deque>

#include <boost/signals2.hpp>
#include <QString>

#include "memedar/utils/find.hpp"
#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"
#include "memedar/model/service.hpp"

#include "memedar/view/error_delegate.hpp"
#include "memedar/view/lesson.hpp"

#include "memedar/presenter/controller.hpp"
#include "memedar/presenter/presenter.hpp"
#include "memedar/presenter/lesson_presenter.hpp"


using md::lesson_presenter;

lesson_presenter::lesson_presenter(md::controller& controller,
                                   model::service& service,
                                   view::error_delegate& error_delegate,
                                   view::lesson& lesson,
                                   model::deck::deck& deck)
	: m_controller     {controller}
	, m_service        {service}
	, m_error_delegate {error_delegate}
	, m_lesson         {lesson}
	, m_deck           {deck}
	, m_task_book      {service.get_task_book(deck)}
{
	auto prev {[this]() { m_lesson.redraw(m_task_book.prev_task()); }};
	auto next {[this]() { m_lesson.redraw(m_task_book.next_task()); }};
	
	auto answer_task {[this](const QString& answer) { show_answer(answer); }};
	auto again_task  {[this]() { again(); }};
	auto done_task   {[this](std::time_t gap) { done(gap); }};
	
	auto designer {[this]() { m_controller.add_card(m_deck); }};
	auto update_designer {[this]() { m_controller.update_task(m_deck,
	                                                          m_task_book.current_task()); }};
		
	add_connect(m_lesson.prev_task.connect(prev),
	            m_lesson.next_task.connect(next),
	            m_lesson.answer.connect(answer_task),
	            m_lesson.again.connect(again_task),
	            m_lesson.done.connect(done_task),
	            m_lesson.call_designer.connect(designer),
	            m_lesson.call_update_designer.connect(update_designer));
	run();
}

void lesson_presenter::run()
{
	m_task_book.empty()
		? m_lesson.show()
		: m_lesson.show(m_task_book.current_task(), m_deck);
}

void lesson_presenter::show_answer(const QString& answer)
{
	try {
		decltype(auto) current {m_task_book.current_task()};
		current.state = model::task::state::marking;
		current.user_answer = answer;
		m_lesson.redraw(current);
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}

void lesson_presenter::again()
{
	try {
		decltype(auto) current {m_task_book.current_task()};
		m_service.again_task(current);
		current.state = model::task::state::answering;
		m_task_book.push_back_current();
		m_lesson.redraw(current);
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}

void lesson_presenter::done(std::time_t gap)
{
	try {
		m_service.done_task(m_deck,
		                    m_task_book.current_task(),
		                    gap);
		m_lesson.redraw(m_task_book.next_task());
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}
