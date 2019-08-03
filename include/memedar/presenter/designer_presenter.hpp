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


#ifndef MEMEDAR_DESIGNER_PRESENTER_HPP
#define MEMEDAR_DESIGNER_PRESENTER_HPP


namespace md::model::card {
	class card;
	class card_dto;
}

namespace md::model::deck {
	class deck;
}

namespace md::model::task {
	class task;
}

namespace md::model {
	class service;
}

namespace md::view {
	class error_delegate;
	class designer;
}

namespace md::designer_presenter {
	class presenter;
	
	class card_adder;
	class task_updater;
	
	class deck_adder;
	class deck_updater;
}


class md::designer_presenter::card_adder : public md::presenter
{
public:
	card_adder(md::model::deck::deck& deck,
	           md::model::service& service,
	           md::view::error_delegate& error_delegate,
	           md::view::designer& designer);

	void run() override;
protected:
	void add_card(md::model::card::card_dto&& new_card);
protected:
	md::model::deck::deck& m_deck;
	md::model::service& m_service;
	md::view::error_delegate& m_error_delegate;
	md::view::designer& m_designer;
};


class md::designer_presenter::task_updater : public md::presenter
{
public:
	task_updater(md::model::deck::deck& deck,
	             md::model::task::task& task,
	             md::model::service& service,
	             md::view::error_delegate& error_delegate,
	             md::view::designer& designer);

	void run() override;
protected:
	void update_task(md::model::card::card_dto&& new_card);
protected:
	md::model::deck::deck& m_deck;
	md::model::task::task& m_task;
	md::model::service& m_service;
	md::view::error_delegate& m_error_delegate;
	md::view::designer& m_designer;
};


class md::designer_presenter::deck_adder : public md::presenter
{
public:
	deck_adder(md::model::service& service,
	           md::view::error_delegate& error_delegate,
	           md::view::designer& designer);

	void run() override;
protected:
	void add_deck(md::model::deck::deck_value&& deck_value);
protected:
	md::model::service& m_service;
	md::view::error_delegate& m_error_delegate;
	md::view::designer& m_designer;
};


class md::designer_presenter::deck_updater : public md::presenter
{
public:
	deck_updater(md::model::deck::deck& deck,
	             md::model::service& service,
	             md::view::error_delegate& error_delegate,
	             md::view::designer& designer);

	void run() override;
protected:
	void update_deck(md::model::deck::deck_value&& deck_value);
protected:
	md::model::deck::deck& m_deck;
	md::model::service& m_service;
	md::view::error_delegate& m_error_delegate;
	md::view::designer& m_designer;
};


#endif // MEMEDAR_DESIGNER_PRESENTER_HPP
