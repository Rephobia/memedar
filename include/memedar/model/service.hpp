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


#ifndef MEMEDAR_MODEL_SERVICE_HPP
#define MEMEDAR_MODEL_SERVICE_HPP


namespace md::model::side {
	class side_value;
	class side;
}

namespace md::model::card {
	class card_dto;
	class card;
}

namespace md::model::deck {
	class deck;
}

namespace md::model::task {
	class task;
	class task_book;
}

namespace md::model::dal {
	class mapper;
}

namespace md::model {
	class service;
}


class md::model::service
{
public:
	explicit service(md::model::dal::mapper& mapper);

	void save_card(md::model::deck::deck& deck,
	               md::model::card::card_dto&& new_card);
	void update_card(md::model::card::card& card,
	                 md::model::card::card_dto&& new_card);
	
	void save_deck(md::model::deck::deck&& deck);
	std::deque<md::model::deck::deck>& get_decks();
	
	md::model::task::task_book& get_task_book(md::model::deck::deck& deck);
	void again_card(md::model::task::task& task);
	void done_card(md::model::deck::deck& deck, md::model::task::task& task, std::time_t gap);
protected:
	md::model::dal::mapper& m_mapper;
protected:
	std::deque<md::model::deck::deck> m_decks {};
	std::map<std::int64_t, md::model::task::task_book> m_tasks {};
};


#endif // MEMEDAR_MODEL_SERVICE_HPP
