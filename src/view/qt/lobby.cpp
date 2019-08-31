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
#include <deque>


#include <boost/signals2.hpp>
#include <QString>
#include <QMainWindow>
#include <QLabel>


#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"

#include "memedar/view/lobby.hpp"
#include "memedar/view/qt/ui/button.hpp"
#include "memedar/view/qt/ui/box.hpp"
#include "memedar/view/qt/main_window.hpp"
#include "memedar/view/qt/lobby.hpp"


using md::view::qt::lobby;

lobby::lobby(qt::main_window* main_window)
	: m_main_window {main_window}
{ ;}

void lobby::show(std::deque<md::model::deck::deck>& decks)
{
	auto del_dialog {new ui::box {QBoxLayout::TopToBottom}};	
	auto box {new ui::box {QBoxLayout::TopToBottom}};
	box->put_widget(del_dialog);

	del_dialog->setWindowFlag(Qt::Dialog);
	
	for (auto& e : decks) {

		QString stat {e.name() + "\n" +
		              QString::number(e.noob_cards()) + "\n" +
		              QString::number(e.ready_cards()) + "\n" +
		              QString::number(e.delayed_cards()) + "\n" +
		              QString::number(e.total_cards())};

		auto lesson {new ui::button {stat, [this, &e]()
		                                   { call_lesson(e); }}};
		
		auto update {new ui::button {"rename", [this, &e]()
		                                       { update_deck(e); }}};
		
		auto add {new ui::button {"add", [this, &e]()
		                                 { add_card(e); }}};
		auto del {new ui::button {"del", [this, &e, del_dialog]()
		                                 { show_delete_dialog(e, del_dialog); }}};

		box->put_widget(QBoxLayout::LeftToRight, lesson, update, del, add);
	}


	m_main_window->set_widget(box);

}

void lobby::show_delete_dialog(model::deck::deck& deck, view::qt::ui::box* dialog)
{
	auto label {new QLabel {"Are you sure to delete deck " + deck.name() + "?"}};
	auto ok {new ui::button {"ok", [this, &deck, dialog]()
	                               {
		                               delete_deck(deck);
		                               dialog->hide();
	                               }}};
	auto cancel {new ui::button {"cancel", [this, &deck, dialog]()
	                                       { dialog->hide(); }}};
	dialog->set_widget(label);
	dialog->put_widget(QBoxLayout::LeftToRight, ok, cancel);
	dialog->show();
}
