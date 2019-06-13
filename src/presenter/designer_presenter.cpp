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
#include <boost/signals2.hpp>

#include <QString>

#include "memedar/utils/find.hpp"
#include "memedar/utils/storage.hpp"

#include "memedar/model/deck/deck.hpp"
#include "memedar/model/card_service.hpp"
#include "memedar/model/deck_service.hpp"

#include "memedar/view/error_delegate.hpp"
#include "memedar/view/designer.hpp"
#include "memedar/presenter/designer_presenter.hpp"


using md::designer_presenter;

designer_presenter::designer_presenter(model::deck_service& deck_service,
                                       model::card_service& cards_service,
                                       view::error_delegate& error_delegate,
                                       view::designer& designer)
	: m_deck_service   {deck_service}
	, m_card_service   {cards_service}
	, m_error_delegate {error_delegate}
	, m_designer       {designer}
	, m_quit           {nullptr}
{
	m_designer.add_card.connect([this](std::int64_t id, model::card::card& card)
	                            { add_card(id, std::move(card)); });

	m_designer.add_deck.connect([this](model::deck::deck& deck)
	                            { add_deck(std::move(deck)); });

	m_designer.cancel.connect([this]()
	                          {
		                          if (m_quit) {
			                          m_quit();
		                          }
	                          });
}

void designer_presenter::run(std::function<void()> quit)
{
	m_quit = quit;
	m_designer.show();
}

void designer_presenter::run(const md::model::deck::deck& deck, std::function<void()> quit)
{
	m_quit = quit;
	m_designer.show(deck);
}

void designer_presenter::add_card(std::int64_t id, model::card::card&& card)
{
	auto deck_it {utils::find_by_id(id, m_deck_service)};

	if (deck_it != m_deck_service.end()) {
		m_card_service.save_card(*deck_it, std::move(card));
	}
	else {
		m_error_delegate.show_error("deck (id: "
		                           + QString::number(id)
		                           + ") doesn't exists");
	}
}

void designer_presenter::add_deck(model::deck::deck&& deck)
{
	m_deck_service.save_deck(std::move(deck));
}
