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


#include <ctime>
#include <memory>
#include <deque>

#include <boost/signals2.hpp>
#include <QString>
#include <QMainWindow>

#include "memedar/utils/storage.hpp"

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
	auto box {new ui::box {QBoxLayout::TopToBottom}};

	for (auto& e : decks) {

		QString stat {e.name() +"\n" +
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


		box->put_widget(QBoxLayout::LeftToRight, lesson, update, add);
	}

	m_main_window->set_widget(box);
}
