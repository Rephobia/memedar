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
#include <deque>

#include <QString>

#include "memedar/utils/find.hpp"
#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"
#include "memedar/model/service.hpp"

#include "memedar/view/error_delegate.hpp"
#include "memedar/view/designer.hpp"

#include "memedar/presenter/presenter.hpp"
#include "memedar/presenter/designer_presenter.hpp"


using md::card_designer_presenter;

card_designer_presenter::card_designer_presenter(model::deck::deck& deck,
                                                 model::service& service,
                                                 view::error_delegate& error_delegate,
                                                 view::designer& designer)
	: m_deck           {deck}
	, m_service        {service}
	, m_error_delegate {error_delegate}
	, m_designer       {designer}
{
	auto action {[this](model::card::card_dto& new_card)
	             { add_card(std::move(new_card)); }};
	
	add_connect(m_designer.add_card.connect(action));
	
	run();
}

void card_designer_presenter::run()
{
	m_designer.show(m_deck);	
}

void card_designer_presenter::add_card(md::model::card::card_dto&& new_card)
{
	try {
		m_service.save_card(m_deck, std::move(new_card));
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}

using md::update_designer_presenter;

update_designer_presenter::update_designer_presenter(model::deck::deck& deck,
                                                     model::task::task& task,
                                                     model::service& service,
                                                     view::error_delegate& error_delegate,
                                                     view::designer& designer)
	: m_deck           {deck}
	, m_task           {task}
	, m_service        {service}
	, m_error_delegate {error_delegate}
	, m_designer       {designer}
{
	auto action {[this](md::model::card::card_dto& new_card)
	             { update_card(std::move(new_card)); }};
	
	add_connect(m_designer.add_card.connect(action));
	
	run();
}


void update_designer_presenter::run()
{
	m_designer.show(m_deck,
	                m_task.card->question.text(), m_task.card->answer.text());
}

void update_designer_presenter::update_card(md::model::card::card_dto&& new_card)
{
	try {
		m_service.update_card(*m_task.card, std::move(new_card));
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}


using md::deck_designer_presenter;

deck_designer_presenter::deck_designer_presenter(model::service& service,
                                                 view::error_delegate& error_delegate,
                                                 view::designer& designer)
	: m_service        {service}
	, m_error_delegate {error_delegate}
	, m_designer       {designer}
{
	auto action {[this](model::deck::deck_value& deck_value)
	             { add_deck(std::move(deck_value)); }};
	
	add_connect(m_designer.add_deck.connect(action));
	
	run();
}

void deck_designer_presenter::run()
{
	m_designer.show();	
}

void deck_designer_presenter::add_deck(model::deck::deck_value&& deck_value)
{
	try {
		m_service.save_deck(std::move(deck_value));
		m_designer.cancel();
	}
	catch (std::system_error& e) {
		m_error_delegate.show_error(e);
	}
}
