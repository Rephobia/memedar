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
#include "memedar/view/qt/lesson_painter.hpp"
#include "memedar/view/qt/lesson.hpp"


using md::view::qt::lesson;

lesson::lesson(md::view::qt::main_window* main_window)
	: m_main_window {main_window}
{ ;}

void lesson::show()
{
	auto label {new QLabel {"the deck doesn't have tasks"}};
	auto designer {new ui::button {"add_card", [this]() { add_card(); }}};
	m_main_window->set_widget(new ui::box {QBoxLayout::TopToBottom, label, designer});
}

void lesson::show(const md::model::task::task& task,
                  const md::model::deck::deck& deck)
{
	auto prev {new md::view::qt::ui::button {"prev", [this]()
	                                                 { prev_task(); }}};
	auto next {new md::view::qt::ui::button {"next", [this]()
	                                                 { next_task(); }}};
	auto iter {new ui::box {QBoxLayout::LeftToRight, prev, next}};


	auto painter {new qt::lesson_painter {deck, *this}};

	re_draw.disconnect_all_slots();
	re_draw.connect([painter](const md::model::task::task& task)
	                { painter->draw(task); });

	auto box {new ui::box {QBoxLayout::TopToBottom, iter, painter}};
	m_main_window->set_widget(box);
	painter->draw(task);
}

