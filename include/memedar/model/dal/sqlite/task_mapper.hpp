/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2018 Roman Erdyakov (Linhurdos) <teremdev@gmail.com>

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


#ifndef MEMEDAR_MODEL_DAL_SQLITE_TASK_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_SQLITE_TASK_MAPPER_HPP


namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
}

namespace md::model::task {
	class task;
	class task_book;
}

namespace md::model::dal::sqlite {
	class task_mapper;
}

class md::model::dal::sqlite::task_mapper : public md::model::dal::task_mapper
{
public:
	explicit task_mapper(md::model::dal::sqlite::adapter::handle& db);

	void create_table() override;

	void save_task(const md::model::deck::deck& deck,
	               const md::model::task::task& task) override;
	void load_task_book(md::model::deck::deck& deck, task::task_book& task_book) override;

	void delete_card(const md::model::card::card& card) override;
	void change_state(md::model::task::task& task, md::model::task::state state) override;
	void delete_done_task(md::model::deck::deck& deck) override;
protected:
	md::model::dal::sqlite::adapter::handle& m_db;
};


#endif // MEMEDAR_MODEL_DAL_SQLITE_TASK_MAPPER_HPP
