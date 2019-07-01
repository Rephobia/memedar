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

#include "memedar/view/lobby.hpp"
#include "memedar/view/menu.hpp"
#include "memedar/view/designer.hpp"
#include "memedar/view/lesson.hpp"

#include "memedar/presenter/presenter.hpp"
#include "memedar/presenter/menu_presenter.hpp"
#include "memedar/presenter/lobby_presenter.hpp"
#include "memedar/presenter/lesson_presenter.hpp"
#include "memedar/presenter/designer_presenter.hpp"
#include "memedar/presenter/controller.hpp"


using md::controller;

controller::~controller() = default;

controller::controller(md::model::card_service& card_service,
                       md::model::deck_service& deck_service,
                       md::model::task_service& task_service,
                       md::view::menu& menu,
                       md::view::lobby& lobby,
                       md::view::lesson& lesson,
                       md::view::designer& designer)
	: m_card_service       {card_service}
	, m_deck_service       {deck_service}
	, m_task_service       {task_service}
	, m_menu               {menu}
	, m_lobby              {lobby}
	, m_lesson             {lesson}
	, m_designer           {designer}
	, m_presenter          {nullptr}
	, m_designer_presenter {nullptr}
{
	m_designer.cancel.connect([this]() { m_presenter->run(); });
	run_lobby();
}

void controller::run_lobby()
{
	m_presenter = std::make_unique<md::lobby_presenter>(*this, m_deck_service, m_lobby);
}

void controller::run_designer(md::model::deck::deck& deck)
{
	m_designer_presenter = std::make_unique<md::designer_presenter>(deck, m_card_service,
	                                                                m_deck_service,
	                                                                m_designer);	
}

void controller::run_lesson(md::model::deck::deck& deck)
{
	m_presenter = std::make_unique<md::lesson_presenter>(*this, deck, m_deck_service,
	                                                     m_task_service,
	                                                     m_lesson);	
}
