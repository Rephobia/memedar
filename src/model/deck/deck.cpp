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

#include "memedar/utils/storage.hpp"
#include "memedar/model/deck/storage.hpp"
#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"


using md::model::deck::deck_value;

deck_value::deck_value(QString&& name)
	: deck::time  {time {}}
	, deck::limit {limit {}}
	, deck::gaps  {gaps {}}
	, m_name      {std::move(name)}
{ ;}

deck_value::deck_value(QString&& name,
                       deck::time time,
                       deck::limit limit,
                       deck::gaps gaps)
	: deck::time  {time}
	, deck::limit {limit}
	, deck::gaps  {gaps}
	, m_name      {std::move(name)}
{ ;}

deck_value::deck_value(deck_value&& other)
	: deck::time  {static_cast<deck::time>(other)}
	, deck::limit {static_cast<deck::limit>(other)}
	, deck::gaps  {static_cast<deck::gaps>(other)}
	, m_name      {std::move(other.m_name)}
{ ;}

deck_value& deck_value::operator=(deck_value&& other)
{
	if (this != &other) {
		time::operator=(static_cast<deck::time>(other));
		limit::operator=(static_cast<deck::limit>(other));
		gaps::operator=(static_cast<deck::gaps>(other));
		m_name = std::move(other.m_name);
	}

	return *this;
}

const QString& deck_value::name() const
{
	return m_name;
}

QString& deck_value::name()
{
	return m_name;
}

void deck_value::change_name(QString&& name)
{
	m_name = name;
}


using md::model::deck::deck;

deck::deck(identity id,
           deck::deck_value&& value)
	: identity   {id}
	, deck_value {std::move(value)}
{ ;}

deck::deck(identity id,
           deck::deck_value&& value,
           md::model::deck::accountant&& accountant)
	: identity         {id}
	, deck::deck_value {std::move(value)}
	, m_accountant     {std::move(accountant)}
{ ;}


void deck::process_card(card::card& card)
{
	m_accountant.process_card(card);
}

void deck::add_card(card::card&& card)
{
	if (deck_storage::is_empty()) {
		deck_storage::need_cards(*this);
	}
	else {
		m_accountant.process_card(card);
		auto shared_card {std::make_shared<card::card>(std::move(card))};
		deck_storage::add(shared_card);
		deck_storage::card_added(*this, shared_card);
	}

}

md::utils::storage<std::shared_ptr<md::model::card::card>>& deck::cards()
{
	if (deck_storage::is_empty()) {
		deck_storage::need_cards(*this);
	}
		
	return static_cast<storage&>(*this);
}


std::int64_t deck::noob_cards() const
{
	return m_accountant.noob_cards(deck_storage::is_loaded());
}

std::int64_t deck::ready_cards() const
{
	return m_accountant.ready_cards(deck_storage::is_loaded());
}

std::int64_t deck::delayed_cards() const
{
	return m_accountant.delayed_cards(deck_storage::is_loaded());
}

std::int64_t deck::total_cards() const
{
	return m_accountant.total_cards(deck_storage::is_loaded());
}
