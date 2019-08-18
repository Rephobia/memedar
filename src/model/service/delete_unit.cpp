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


#include <deque>

#include "memedar/utils/storage.hpp"

#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"

#include "memedar/model/dal/transaction_guard.hpp"
#include "memedar/model/dal/mapper.hpp"

#include "memedar/model/service/delete_unit.hpp"


using md::model::delete_unit;

delete_unit::delete_unit(dal::mapper& mapper)
	: deck_to_taskbook {mapper}
	, m_mapper {mapper}
{ ;}

void delete_unit::delete_deck(md::model::deck::deck& deck)
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	m_mapper.delete_deck(deck);

	deck_to_taskbook::delete_deck(deck);
	
	transaction.commit();
}
