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


#ifndef MEMEDAR_MODEL_TASK_TASK_BOOK_HPP
#define MEMEDAR_MODEL_TASK_TASK_BOOK_HPP


namespace md::utils {
	template<class T>
	class storage;
}

namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
}

namespace md::model::task {
	enum class state : int;
	class task;

	class add_visitor;
	class task_book;
}


class md::model::task::task_book : public md::utils::storage<md::model::task::task>
{
public:
	explicit task_book(md::model::deck::deck& deck);
	bool add_card(md::model::card::card& card);
	void add_card(md::model::card::card& card, md::model::task::state state);

	std::int64_t noob_space() const;
	std::int64_t ready_space() const;
	std::int64_t space() const;

	md::model::task::task& current_task();
	md::model::task::task& prev_task();
	md::model::task::task& next_task();

	void push_back_current();

	md::model::deck::deck& deck;
private:
	friend class md::model::task::add_visitor;
	using storage::add;
protected:
	std::int64_t m_noob_space;
	std::int64_t m_ready_space;
	std::size_t m_current_index;
};



#endif // MEMEDAR_MODEL_TASK_TASK_BOOK_HPP
