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

#include <boost/signals2.hpp>

#include "memedar/presenter/menu_presenter.hpp"
#include "memedar/presenter/lobby_presenter.hpp"
#include "memedar/presenter/designer_presenter.hpp"
#include "memedar/presenter/lesson_presenter.hpp"
#include "memedar/presenter/controller.hpp"


using md::controller;

controller::controller(md::menu_presenter& menu,
                       md::lobby_presenter& lobby,
                       md::designer_presenter& designer,
                       md::lesson_presenter& lesson)
	: m_menu     {menu}
	, m_lobby    {lobby}
	, m_designer {designer}
	, m_lesson   {lesson}
{
	auto run_lobby {[this] { m_lobby.run(); }};
	m_menu.go_to_designer.connect([this, run_lobby]() { m_designer.run(run_lobby); });

	m_lobby.go_to_lesson.connect([this](std::int64_t id)
	                             { m_lesson.run(id); });

	m_lobby.go_to_designer.connect([this, run_lobby](const md::model::deck::deck& deck)
	                               { m_designer.run(deck, run_lobby); });
	m_lobby.run();
}
