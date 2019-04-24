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
#include <memory>

#include <QString>

#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"

#include "memedar/model/dal/transaction.hpp"
#include "memedar/model/dal/card_mapper.hpp"
#include "memedar/model/dal/deck_mapper.hpp"
#include "memedar/model/dal/transaction_guard.hpp"

#include "memedar/view/error_delegate.hpp"
#include "memedar/model/deck_service.hpp"


using md::model::deck_service;

deck_service::deck_service(md::view::error_delegate& error_delegate,
                           dal::transaction& transaction,
                           dal::card_mapper& card_mapper,
                           dal::deck_mapper& deck_mapper)
	: storage          {utils::storage<deck::deck> {}}
	, m_error_delegate {error_delegate}
	, m_transaction    {transaction}
	, m_card_mapper    {card_mapper}
	, m_deck_mapper    {deck_mapper}
{
	load_decks();
}

void deck_service::save_deck(deck::deck&& deck)
{
	try {
		auto guard {dal::make_transaction(m_transaction)};

		m_deck_mapper.save_deck(deck);
		storage::add(std::move(deck));

		guard.commit();
	}
	catch (std::system_error &e) {
		m_error_delegate.show_error(e);
	}
}

void deck_service::load_decks()
{
	try {
		auto guard {dal::make_transaction(m_transaction)};

		storage::operator=(m_deck_mapper.load_decks());

		guard.commit();
	}
	catch (std::system_error &e) {
		m_error_delegate.show_error(e);
	}
}
