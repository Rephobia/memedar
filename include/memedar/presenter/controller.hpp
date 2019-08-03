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


#ifndef MEMEDAR_CONTROLLER_HPP
#define MEMEDAR_CONTROLLER_HPP


namespace md::model::deck {
	class deck;
}

namespace md::model {
	class service;
}

namespace md::view {
	class error_delegate;
	class menu;
	class lobby;
	class designer;
	class lesson;
}

namespace md {
	class presenter;
	class controller;
}


class md::controller
{
public:
	controller(md::model::service& service,
	           md::view::error_delegate& error_delegate,
	           md::view::menu& menu,
	           md::view::lobby& lobby,
	           md::view::lesson& lesson,
	           md::view::designer& designer);
       
	void run_lobby();
	void run_lesson(md::model::deck::deck& deck);
	
	void add_card(md::model::deck::deck& deck);
	void update_task(md::model::deck::deck& deck, md::model::task::task& task);
	void add_deck();
	void update_deck(md::model::deck::deck& deck);
	
	~controller();
protected:
	md::model::service& m_service;

	md::view::error_delegate& m_error_delegate;
	md::view::menu& m_menu;
	md::view::lobby& m_lobby;
	md::view::lesson& m_lesson;
	md::view::designer& m_designer;
protected:
	std::unique_ptr<md::presenter> m_presenter;
	std::unique_ptr<md::presenter> m_designer_presenter;

};


#endif // MEMEDAR_CONTROLLER_HPP
