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
#include <memory>
#include <map>
#include <deque>

#include <QString>

#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"

#include "memedar/model/dal/mapper.hpp"

#include "memedar/model/deck_service.hpp"


using md::model::deck_service;

deck_service::deck_service(dal::mapper& mapper)
	: m_mapper {mapper}
{ ;}

void deck_service::save_deck(deck::deck&& deck)
{
	m_mapper.save_deck(m_decks, std::move(deck));
}

std::deque<md::model::deck::deck>& deck_service::get_decks()
{
	if (m_decks.empty()) {
		m_decks = m_mapper.load_decks();
	}
	return m_decks;
}
