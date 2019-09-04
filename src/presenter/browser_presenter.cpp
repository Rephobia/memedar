/*
 * SPDX-License-Identifier: GPL-3.0-or-later
k
 * Copyright (C) 2019 Roman Erdyakov

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

#include <QString>
#include <boost/signals2.hpp>

#include "memedar/utils/storage.hpp"

#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/taskbook.hpp"
#include "memedar/model/service/service.hpp"

#include "memedar/view/error_delegate.hpp"
#include "memedar/view/browser.hpp"

#include "memedar/presenter/presenter.hpp"
#include "memedar/presenter/browser_presenter.hpp"
#include "memedar/presenter/controller.hpp"


using md::browser_presenter;

browser_presenter::browser_presenter(md::controller& controller,
                                     md::model::service& service,
                                     md::view::error_delegate& error_delegate,
                                     md::view::browser& browser)
	: m_controller     {controller}
	, m_service        {service}
	, m_error_delegate {error_delegate}
	, m_browser        {browser}
{
	auto del_card {[this](model::deck::deck& deck,
	                      model::card::card& card)
	                  { delete_card(deck, card); }};

	add_connect(m_browser.delete_card.connect(del_card));
	run();
}

void browser_presenter::run()
{
	m_browser.show(m_service.get_decks());
}

void browser_presenter::delete_card(model::deck::deck& deck, model::card::card& card)
{
	try {
		m_service.delete_card(deck, card);
		run();
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}
