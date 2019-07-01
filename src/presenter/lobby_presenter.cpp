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

#include <QString>
#include <boost/signals2.hpp>

#include "memedar/utils/find.hpp"
#include "memedar/utils/storage.hpp"

#include "memedar/model/deck/deck.hpp"
#include "memedar/model/deck_service.hpp"

#include "memedar/view/lobby.hpp"

#include "memedar/presenter/presenter.hpp"
#include "memedar/presenter/lobby_presenter.hpp"
#include "memedar/presenter/controller.hpp"


using md::lobby_presenter;

lobby_presenter::lobby_presenter(md::controller& controller,
                                 md::model::deck_service& deck_service,
                                 md::view::lobby& lobby)
	: m_controller   {controller}
	, m_deck_service {deck_service}
	, m_lobby        {lobby}
{
	add_connect(m_lobby.call_lesson.connect([this](std::int64_t id)
	                                        { run_lesson(id); }));
	add_connect(m_lobby.call_designer.connect([this](std::int64_t id)
	                                          { run_designer(id); }));
	
	m_lobby.show(deck_service);
}

void lobby_presenter::run()
{
	m_lobby.show(m_deck_service);
}

void lobby_presenter::run_lesson(std::int64_t id)
{
	m_controller.run_lesson(*utils::find_by_id(id, m_deck_service));	
}

void lobby_presenter::run_designer(std::int64_t id)
{
	m_controller.run_designer(*utils::find_by_id(id, m_deck_service));	
}
