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


#ifndef MEMEDAR_MODEL_DECK_TO_TASKBOOK_HPP
#define MEMEDAR_MODEL_DECK_TO_TASKBOOK_HPP


#include <map>
#include <deque>


namespace md::model {
	class deck_to_taskbook;
}


class md::model::deck_to_taskbook
{
public:
	using iterator = std::map<std::int64_t,
	                          md::model::task::task_book>::iterator;

	iterator begin();
	iterator end();
	
	std::deque<md::model::deck::deck>& get_decks();
	iterator get_taskbook(md::model::deck::deck& deck);
	
	iterator add_taskbook(md::model::deck::deck& deck,
	                      md::model::task::task_book&& task_book);
	
protected:
	std::deque<md::model::deck::deck> m_decks {};
	std::map<std::int64_t, md::model::task::task_book> m_tasks {};	
};


#endif // MEMEDAR_MODEL_DECK_TO_TASKBOOK_HPP
