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


#include "memedar/utils/storage.hpp"

#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"
#include "memedar/model/deck_to_taskbook.hpp"


using md::model::deck_to_taskbook;


std::deque<md::model::deck::deck>& deck_to_taskbook::get_decks()
{
	return m_decks;
}

deck_to_taskbook::iterator deck_to_taskbook::begin()
{
	return m_tasks.begin();
}

deck_to_taskbook::iterator deck_to_taskbook::end()
{
	return m_tasks.end();
}

deck_to_taskbook::iterator deck_to_taskbook::add_taskbook(deck::deck& deck,
                                                          task::task_book&& book)
{
	decltype(auto) pair = std::make_pair(deck.id(), std::move(book));
	return m_tasks.insert(std::move(pair)).first;
}

deck_to_taskbook::iterator deck_to_taskbook::get_taskbook(md::model::deck::deck& deck)
{
	return m_tasks.find(deck.id());
}
