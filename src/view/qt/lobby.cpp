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

void lobby::show(const utils::storage<model::deck::deck>& decks)
{
	auto box {new ui::box {QBoxLayout::TopToBottom}};

	for (decltype(auto) e : decks) {

		QString stat {e.name() +"\n" +
		              QString::number(e.noob_cards()) + "\n" +
		              QString::number(e.ready_cards()) + "\n" +
		              QString::number(e.delayed_cards()) + "\n" +
		              QString::number(e.total_cards())};

		auto btn {new ui::button {stat, [this, &e]()
		                                { go_to_lesson(e.id()); }}};
		auto designer {new ui::button {"add", [this, &e]()
		                                      { go_to_designer(e); }}};

		box->put_widget(QBoxLayout::LeftToRight, btn, designer);
	}

	m_main_window->set_widget(box);
}
