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

namespace md {
	class presenter;
	class card_designer_presenter;
	class deck_designer_presenter;
	class update_designer_presenter;
}


class md::card_designer_presenter : public md::presenter
{
public:
	card_designer_presenter(md::model::deck::deck& deck,
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

class md::update_designer_presenter : public md::presenter
{
public:
	update_designer_presenter(md::model::deck::deck& deck,
	                          md::model::task::task& task,
	                          md::model::service& service,
	                          md::view::error_delegate& error_delegate,
	                          md::view::designer& designer);

	void run() override;
protected:
	void update_card(md::model::card::card_dto&& new_card);
protected:
	md::model::deck::deck& m_deck;
	md::model::task::task& m_task;
	md::model::service& m_service;
	md::view::error_delegate& m_error_delegate;
	md::view::designer& m_designer;
};


class md::deck_designer_presenter : public md::presenter
{
public:
	deck_designer_presenter(md::model::service& service,
	                        view::error_delegate& error_delegate,
	                        md::view::designer& designer);

	void run() override;
protected:
	void add_deck(md::model::deck::deck&& deck);
protected:
	md::model::service& m_service;
	md::view::error_delegate& m_error_delegate;
	md::view::designer& m_designer;
};


#endif // MEMEDAR_DESIGNER_PRESENTER_HPP
