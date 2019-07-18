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


#ifndef MEMEDAR_MODEL_DAL_TASK_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_TASK_MAPPER_HPP


namespace md::model::deck {
	class deck;
}

namespace md::model::task {
	enum class state : int;
	class task;
	class task_book;
}

namespace md::model::dal {
	class task_mapper;
}


class md::model::dal::task_mapper
{
public:
	virtual void create_table() = 0;

	virtual	void save_task(const md::model::deck::deck& deck,
		               const md::model::task::task& task) = 0;
	virtual void load_task_book(md::model::deck::deck& deck, task::task_book& task_book) = 0;

	virtual void change_state(md::model::task::task& task, md::model::task::state state) = 0;
	virtual void delete_done_task(md::model::deck::deck& deck) = 0;

	virtual ~task_mapper() = default;
};


#endif // MEMEDAR_MODEL_DAL_TASK_MAPPER_HPP
