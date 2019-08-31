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


#include <boost/signals2.hpp>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QMainWindow>


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

void designer::show_card(const model::deck::deck& deck)
{
	auto deck_name {new QLabel {deck.name()}};
	auto question {new QTextEdit {}};
	auto answer {new QTextEdit {}};
	auto typing {new QCheckBox {"typing"}};
	
	make_card_box(deck_name, question, answer, typing);
}

void designer::show_card(const model::deck::deck& deck,
                         const model::card::card& card)
{
	auto deck_name {new QLabel {deck.name()}};
	auto question {new QTextEdit {card.question.text()}};
	auto answer {new QTextEdit {card.answer.text()}};
	auto typing {new QCheckBox {"typing"}};
	typing->setChecked(card.has_typing);

	make_card_box(deck_name, question, answer, typing);
	
}

void designer::make_card_box(QLabel* deck_name,
                             QTextEdit* question,
                             QTextEdit* answer,
                             QCheckBox* typing)
{
	auto add_action {[this, question, answer, typing]()
	                 {
		                 model::side::side_value q {question->toPlainText()};
		                 model::side::side_value a {answer->toPlainText()};
		                 model::card::card_value card {typing->isChecked()};
		                 model::card::card_dto dto {card, std::move(q), std::move(a)};
		                 get_card(dto);
	                 }};
	
	auto ok {new ui::button {"ok", add_action}};
	auto close {new ui::button {"close", [this]() { cancel(); }}};

	auto box {new ui::box {QBoxLayout::TopToBottom,
	                       deck_name, typing, question, answer}};
	box->put_widget(QBoxLayout::LeftToRight, ok, close);
	
	m_main_window->set_widget(box);	
}

void designer::show_deck()
{
	auto edit {new QLineEdit {}};
	make_deck_box(edit);
}

void designer::show_deck(const md::model::deck::deck& deck)
{
	auto edit {new QLineEdit {deck.name()}};
	make_deck_box(edit);
}

void designer::make_deck_box(QLineEdit* edit_line)
{
	auto add_action {[this, edit_line]()
	                 {
		                 model::deck::deck_value value {edit_line->text()};
		                 get_deck(value);
	                 }};

	auto ok {new ui::button {"ok", add_action}};
	auto close {new ui::button {"close", [this]() { cancel(); }}};

	auto box {new ui::box {QBoxLayout::TopToBottom, edit_line}};
	box->put_widget(QBoxLayout::LeftToRight, ok, close);

	m_main_window->set_widget(box);	
}
