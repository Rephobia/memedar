/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov

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


using md::model::deck::storage_status;

bool storage_status::is_empty() const
{
	return m_status == status::empty;
}

bool storage_status::is_loaded() const
{
	return m_status == status::loaded;
}

void storage_status::set_status(storage_status::status status)
{
	m_status = status;
}


using md::model::deck::storage_container;

void storage_container::add_card(shared_card card)
{
	m_storage.add(card);
}

md::utils::storage<storage_container::shared_card>& storage_container::cards()
{
	return static_cast<md::utils::storage<shared_card>&>(m_storage);
}


using md::model::deck::storage;

storage::storage(md::model::deck::storage&& other)
	: storage_status    {static_cast<storage_status&>(other)}
	, storage_container {std::move(static_cast<storage_container&>(other))}
	, need_cards        {std::move(other.need_cards)}
	, card_added        {std::move(other.card_added)}
{;}

md::model::deck::storage& storage::operator=(md::model::deck::storage&& other)
{
	if (this != &other) {
		storage_status::operator=(static_cast<storage_status&>(other));
		storage_container::operator=(std::move(static_cast<storage_container&>(other)));
		need_cards = std::move(other.need_cards);
		card_added = std::move(other.card_added);
	}
	
	return *this;
}

storage::boss storage::get_storage_boss()
{
	return boss {*this};
}


storage::boss::boss(storage& storage)
	: m_commit  {false}
	, m_storage {storage}
{
	m_storage.set_status(status::loading);
}

void storage::boss::commit()
{
	m_storage.set_status(status::loaded);
	m_commit = true;
}

storage::boss::~boss()
{
	if (not m_commit) {
		m_storage.set_status(status::empty);
	}
}
