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


#ifndef MEMEDAR_MODEL_DAL_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_MAPPER_HPP


namespace md::model::side {
	class side;
	class side_value;
}

namespace md::model::card {
	class card;
	class card_dto;
}

namespace md::model::deck {
	class deck;
	class deck_value;
}

namespace md::model::dal {
	class mapper;
	class transaction_guard;
}

namespace md::model::task {
	class task;
	class task_book;
}


class md::model::dal::mapper
{
public:
	virtual md::model::dal::transaction_guard make_transaction() = 0;
	virtual	void save_card(md::model::deck::deck& deck,
		               md::model::task::task_book& task_book,
		               md::model::card::card_dto&& new_card) = 0;
	virtual	void reset_task(md::model::task::task& task) = 0;
	
	virtual	void save_deck(std::deque<md::model::deck::deck>& decks,
		               md::model::deck::deck_value&& deck_value) = 0;
	virtual	std::deque<md::model::deck::deck> load_decks() = 0;
	
	virtual void update_side(md::model::side::side& old_side,
	                         md::model::side::side_value&& new_side) = 0;
	
	virtual void update_card(md::model::card::card& card, bool typing) = 0;
	
	virtual md::model::task::task_book make_task_book(md::model::deck::deck& deck) = 0;
	virtual void done_noob(md::model::deck::deck& deck,
	                       md::model::task::task& task, std::time_t gap) = 0;
	virtual void done_ready(md::model::deck::deck& deck,
	                        md::model::task::task& task, std::time_t gap) = 0;
	
	virtual ~mapper() = default;
};


#endif // MEMEDAR_MODEL_DAL_MAPPER_HPP
