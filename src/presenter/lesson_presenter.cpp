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
#include <memory>
#include <boost/signals2.hpp>

#include <QString>

#include "memedar/utils/find.hpp"
#include "memedar/utils/storage.hpp"
#include "memedar/utils/ref_wrapper.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"
#include "memedar/model/deck_service.hpp"
#include "memedar/model/task_service.hpp"

#include "memedar/view/error_delegate.hpp"
#include "memedar/view/lesson.hpp"
#include "memedar/presenter/lesson_presenter.hpp"

using md::lesson_presenter;

lesson_presenter::~lesson_presenter() = default;

lesson_presenter::lesson_presenter(model::deck_service& deck_service,
                                   model::task_service& task_service,
                                   view::error_delegate& error_delegate,
                                   view::lesson& lesson)
	: m_deck_service   {deck_service}
	, m_task_service   {task_service}
	, m_error_delegate {error_delegate}
	, m_lesson         {lesson}
	, m_task_book      {nullptr}
{
	m_lesson.prev_task.connect([this]() { m_lesson.redraw(m_task_book->prev_task()); });
	m_lesson.next_task.connect([this]() { m_lesson.redraw(m_task_book->next_task()); });
	m_lesson.answer.connect([this]() { show_answer(); });
	m_lesson.answer_text.connect([this](const QString answer)
	                             { show_answer(answer); });
	m_lesson.again.connect([this]() { again(); });
	m_lesson.done.connect([this](std::time_t gap) { done(gap); });
	m_lesson.call_designer.connect([this]() { go_to_designer(m_task_book->deck, [this]() { run_current(); }); });
}

void lesson_presenter::run(std::int64_t deck_id)
{
	using md::model::task::task_book;
	decltype(auto) deck {utils::find_by_id(deck_id, m_deck_service)};
	m_task_book = std::make_unique<task_book>(m_task_service.make_task(*deck));
	
	m_task_book->empty()
		? m_lesson.show()
		: m_lesson.show(m_task_book->current_task(), m_task_book->deck);
}

void lesson_presenter::run_current()
{
	m_task_service.update_task_book(*m_task_book);
	
	m_task_book->empty()
		? m_lesson.show()
		: m_lesson.show(m_task_book->current_task(), m_task_book->deck);
}

void lesson_presenter::show_answer()
{
	decltype(auto) current {m_task_book->current_task()};
	current.state = model::task::state::marking;
	m_lesson.redraw(current);
}

void lesson_presenter::show_answer(const QString& answer)
{
	decltype(auto) current {m_task_book->current_task()};
	current.state = model::task::state::marking;
	current.user_answer = answer;
	m_lesson.redraw(current);
}

void lesson_presenter::again()
{
	decltype(auto) current {m_task_book->current_task()};
	m_task_service.again_card(current);
	current.state = model::task::state::answering;
	m_task_book->push_back_current();
	m_lesson.redraw(current);
}

void lesson_presenter::done(std::time_t gap)
{
	m_task_service.done_card(m_task_book->deck,
	                         m_task_book->current_task(),
	                         gap);
	m_lesson.redraw(m_task_book->next_task());

}
