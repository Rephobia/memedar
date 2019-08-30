/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov (Linhurdos) <teremdev@gmail.com>

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


#include "memedar/model/deck/storage.hpp"


using md::model::deck::deck_storage;

md::model::deck::deck_storage::deck_storage()
	: m_status {status::empty}
{ ;}

deck_storage::deck_storage(md::model::deck::deck_storage&& other)
	: storage    {std::move(static_cast<storage&>(other))}
	, need_cards {std::move(other.need_cards)}
	, card_added {std::move(other.card_added)}
	, m_status   {other.m_status}
{;}

md::model::deck::deck_storage& deck_storage::operator=(md::model::deck::deck_storage&& other)
{
	if (this != &other) {
		storage::operator=(std::move(static_cast<storage&>(other)));
		need_cards = std::move(other.need_cards);
		card_added = std::move(other.card_added);
		m_status = other.m_status;
	}
	
	return *this;
}

bool deck_storage::is_empty() const
{
	return m_status == status::empty;
}

bool deck_storage::is_loaded() const
{
	return m_status == status::loaded;
}

deck_storage::boss deck_storage::get_storage_boss()
{
	return boss {*this};
}

void deck_storage::set_status(md::model::deck::deck_storage::status status)
{
	m_status = status;
}

deck_storage::boss::boss(deck_storage& deck_storage)
	: m_commit  {false}
	, m_storage {deck_storage}
{
	m_storage.set_status(status::loading);
}

void deck_storage::boss::commit()
{
	m_storage.set_status(status::loaded);
	m_commit = true;
}

deck_storage::boss::~boss()
{
	if (not m_commit) {
		m_storage.set_status(status::empty);
	}
}
