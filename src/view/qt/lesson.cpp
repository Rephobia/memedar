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


#include <boost/signals2.hpp>

#include <QLabel>
#include <QTextEdit>
#include <QMainWindow>
#include <QString>
#include <QCheckBox>
#include <QLineEdit>

#include "memedar/utils/storage.hpp"
#include "memedar/utils/ref_wrapper.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"

#include "memedar/view/lesson.hpp"
#include "memedar/view/qt/ui/button.hpp"
#include "memedar/view/qt/ui/box.hpp"
#include "memedar/view/qt/main_window.hpp"
#include "memedar/view/qt/lesson.hpp"


using md::view::qt::lesson;

lesson::lesson(md::view::qt::main_window* main_window)
	: m_main_window {main_window}
{ ;}

void lesson::show(const md::model::task::task& task,
                  const md::model::deck::deck& deck)
{
	auto prev {new md::view::qt::ui::button {"prev", [this]()
	                                                 { prev_task(); }}};
	auto next {new md::view::qt::ui::button {"next", [this]()
	                                                 { next_task(); }}};
	auto iter {new ui::box {QBoxLayout::LeftToRight, prev, next}};


	auto painter {new lesson::painter {deck, *this}};

	re_draw.disconnect_all_slots();
	re_draw.connect([painter](const md::model::task::task& task)
	                { painter->draw(task); });

	auto box {new ui::box {QBoxLayout::TopToBottom, iter, painter}};
	m_main_window->set_widget(box);
	painter->draw(task);
}


lesson::painter::painter(const md::model::deck::deck& deck,
                           md::view::qt::lesson& lesson)
	: box       {QBoxLayout::TopToBottom}
	, m_deck    {deck}
	, m_lesson  {lesson}
{ ;}

void lesson::painter::answering_state(const model::card::card& card)
{
	auto question {new QLabel {card.question.text()}};
	auto button {new ui::button {"show", [this]() { m_lesson.answer(); }}};
	box::set_widget(question, button);

}

void lesson::painter::answering_state_input(const model::card::card& card)
{
	auto question {new QLabel {card.question.text()}};
	auto edit {new QLineEdit {}};
	auto show_btn {new ui::button {"show",
	                               [this, edit]()
	                               { m_lesson.answer_text(edit->text()); }}};
	box::set_widget(question, edit, show_btn);

}

void lesson::painter::marking_state(const model::task::task& task)
{
	const model::card::card& card {task.card.get()};

	auto question {new QLabel {card.question.text()}};
	auto user_answer {new QLabel {task.user_answer}};
	auto answer {new QLabel {card.answer.text()}};

	auto good_intvl {card.get_interval(m_deck.good_gap())};
	auto easy_intvl {card.get_interval(m_deck.easy_gap())};

	auto again {new ui::button {"again\n", [this]() { m_lesson.again();}}};

	auto good {new ui::button {"good\n" + QString::number(good_intvl),
	                           [this, good_intvl]()
	                           { m_lesson.done(good_intvl); }}};

	auto easy {new ui::button {"easy\n" + QString::number(easy_intvl),
	                           [this, easy_intvl]()
	                           { m_lesson.done(easy_intvl); }}};

	box::set_widget(question, user_answer, answer);
	box::put_widget(QBoxLayout::LeftToRight, again, good, easy);
}

void lesson::painter::done_state(const model::card::card& card)
{
	auto question {new QLabel {card.question.text()}};
	auto answer {new QLabel {card.answer.text()}};
	box::set_widget(question, answer);
}

void lesson::painter::draw(const model::task::task& task)
{
	switch (task.state) {
	case md::model::task::state::answering: {
		task.card.get().has_typing()
			? answering_state_input(task.card)
			: answering_state(task.card);
		break;
	}
	case md::model::task::state::marking: {
		marking_state(task);
		break;
	}
	case md::model::task::state::done: {
		done_state(task.card);
		break;
	}
	}
}
