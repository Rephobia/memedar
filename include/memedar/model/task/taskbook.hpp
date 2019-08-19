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


#ifndef MEMEDAR_MODEL_TASK_TASKBOOK_HPP
#define MEMEDAR_MODEL_TASK_TASKBOOK_HPP


#include <optional>


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
	class taskbook;
}


class md::model::task::taskbook : public md::utils::storage<md::model::task::task>
{
public:
	explicit taskbook(md::model::deck::deck& deck);

	std::optional<md::model::task::task>
	check_card(std::shared_ptr<md::model::card::card> card,
	           md::model::task::state state = md::model::task::state::answering);
	void add_task(md::model::task::task&& task);

	std::int64_t noob_space() const;
	std::int64_t ready_space() const;
	std::int64_t space() const;

	md::model::task::task& current_task();
	md::model::task::task& prev_task();
	md::model::task::task& next_task();

	void push_back_current();
private:
	using storage::add;
protected:
	std::int64_t m_noob_space;
	std::int64_t m_ready_space;
	std::size_t m_current_index;
};



#endif // MEMEDAR_MODEL_TASK_TASKBOOK_HPP
