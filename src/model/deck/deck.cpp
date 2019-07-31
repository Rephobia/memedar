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


#include <memory>

#include <QString>

#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"

using md::model::deck::deck;

deck::deck(deck::info&& info)
	: deck::identity {identity {}}
	, deck::info     {std::move(info)}
	, deck::time     {time {}}
	, deck::limit    {limit {}}
	, deck::gaps     {gaps {}}
	, m_accountant   {md::model::deck::accountant {}}
{ ;}

deck::deck(deck::identity id,
           deck::info&& info,
           deck::time time,
           deck::limit limit,
           deck::gaps gaps,
           md::model::deck::accountant&& accountant)
	: deck::identity {id}
	, deck::info     {std::move(info)}
	, deck::time     {time}
	, deck::limit    {limit}
	, deck::gaps     {gaps}
	, m_accountant   {std::move(accountant)}
{ ;}

bool deck::operator<(const md::model::deck::deck& other) const
{
	return id() < other.id();
}

void deck::process_card(card::card& card)
{
	m_accountant.process_card(card);
}

std::shared_ptr<md::model::card::card> deck::add_card(card::card&& card)
{
	m_accountant.process_card(card);
	decltype(auto) shared_card {std::make_shared<card::card>(std::move(card))};
	storage::add(shared_card);
	return shared_card;
}

std::int64_t deck::noob_cards() const
{
	return m_accountant.noob_cards(not storage::empty());
}

std::int64_t deck::ready_cards() const
{
	return m_accountant.ready_cards(not storage::empty());
}

std::int64_t deck::delayed_cards() const
{
	return m_accountant.delayed_cards(not storage::empty());
}

std::int64_t deck::total_cards() const
{
	return m_accountant.total_cards(not storage::empty());
}
