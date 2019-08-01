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
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QMainWindow>

#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"

#include "memedar/view/qt/ui/button.hpp"
#include "memedar/view/qt/ui/box.hpp"
#include "memedar/view/qt/main_window.hpp"
#include "memedar/view/designer.hpp"
#include "memedar/view/qt/designer.hpp"


using md::view::qt::designer;

designer::designer(qt::main_window* main_window)
	: m_main_window {main_window}
{ ;}

void designer::show(const model::deck::deck& deck,
                    QString question, QString answer)
{
	auto label {new QLabel {deck.name()}};
	auto q_edit {new QTextEdit {question}};
	auto a_edit {new QTextEdit {answer}};
	auto typing {new QCheckBox {"typing"}};

	auto add_action {[this, q_edit, a_edit, typing]()
	                 {
		                 model::side::side_value q {q_edit->toPlainText()};
		                 model::side::side_value a {a_edit->toPlainText()};
		                 model::card::card_value card {typing->isChecked()};
		                 model::card::card_dto dto {card, std::move(q), std::move(a)};
		                 add_card(dto);
	                 }};

	auto ok {new ui::button {"ok", add_action}};
	auto close {new ui::button {"close", [this]() { cancel(); }}};
	auto box {new ui::box {QBoxLayout::TopToBottom,
	                       label, typing, q_edit, a_edit}};
	box->put_widget(QBoxLayout::LeftToRight, ok, close);
	m_main_window->set_widget(box);
}

void designer::show()
{
	auto edit {new QLineEdit {}};

	auto add_action {[this, edit]()
	                 {
		                 model::deck::deck_value value {edit->text()};
		                 add_deck(value);
	                 }};

	auto ok {new ui::button {"ok", add_action}};
	auto close {new ui::button {"close", [this]() { cancel(); }}};

	auto box {new ui::box {QBoxLayout::TopToBottom, edit}};
	box->put_widget(QBoxLayout::LeftToRight, ok, close);

	m_main_window->set_widget(box);
}
