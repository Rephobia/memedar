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
#include <deque>
#include <optional>

#include <QString>
#include <boost/signals2.hpp>

#include "memedar/utils/storage.hpp"
#include "memedar/view/error_delegate.hpp"
#include "memedar/view/menu.hpp"
#include "memedar/view/lobby.hpp"
#include "memedar/view/designer.hpp"
#include "memedar/view/lesson.hpp"
#include "memedar/view/browser.hpp"

#include "memedar/model/task/task.hpp"
#include "memedar/model/task/taskbook.hpp"

#include "memedar/presenter/presenter.hpp"
#include "memedar/presenter/lobby_presenter.hpp"
#include "memedar/presenter/lesson_presenter.hpp"
#include "memedar/presenter/designer_presenter.hpp"
#include "memedar/presenter/browser_presenter.hpp"

#include "memedar/presenter/controller.hpp"


using md::controller;

controller::~controller() = default;

controller::controller(md::model::service& service,
                       md::view::error_delegate& error_delegate,
                       md::view::menu& menu,
                       md::view::lobby& lobby,
                       md::view::lesson& lesson,
                       md::view::designer& designer,
                       md::view::browser& browser)
	: m_service            {service}
	, m_error_delegate     {error_delegate}
	, m_menu               {menu}
	, m_lobby              {lobby}
	, m_lesson             {lesson}
	, m_designer           {designer}
	, m_browser            {browser}
	, m_presenter          {nullptr}
	, m_designer_presenter {nullptr}
{
	m_menu.call_lobby.connect([this]() { run_lobby(); });
	m_menu.call_designer.connect([this]() { add_deck(); });
	m_menu.call_browser.connect([this]() { run_browser(); });
	m_designer.cancel.connect([this]() { m_presenter->run(); });
	run_lobby();
}

void controller::run_lobby()
{
	try {
		m_presenter = std::make_unique<md::lobby_presenter>
			(*this, m_service, m_error_delegate, m_lobby);
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}

void controller::run_lesson(md::model::deck::deck& deck)
{
	try {
		m_presenter = std::make_unique<md::lesson_presenter>
			(*this, m_service, m_error_delegate, m_lesson, deck);
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}

void controller::run_browser()
{
	try {
		m_presenter = std::make_unique<md::browser_presenter>
			(*this, m_service, m_error_delegate, m_browser);
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}	
}

void controller::add_card(md::model::deck::deck& deck)
{
	try {
		m_designer_presenter = std::make_unique<designer_presenter::card_adder>
			(deck, m_service, m_error_delegate, m_designer);
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}

void controller::update_task(md::model::deck::deck& deck, md::model::task::task& task)
{
	try {
		m_designer_presenter = std::make_unique<designer_presenter::task_updater>
			(deck, task, m_service, m_error_delegate, m_designer);
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}

void controller::add_deck()
{
	try {
		m_designer_presenter = std::make_unique<designer_presenter::deck_adder>
			(m_service, m_error_delegate, m_designer);
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}

void controller::update_deck(model::deck::deck& deck)
{
	try {
		m_designer_presenter = std::make_unique<designer_presenter::deck_updater>
			(deck, m_service, m_error_delegate, m_designer);
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}
