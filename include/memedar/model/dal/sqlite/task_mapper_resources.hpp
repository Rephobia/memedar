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


#ifndef MEMEDAR_MODEL_DAL_TASK_MAPPER_RESOURCES_HPP
#define MEMEDAR_MODEL_DAL_TASK_MAPPER_RESOURCES_HPP


namespace md::model::dal::sqlite {
	class task_index;
	namespace task_resources {
		std::string create_table();

		std::string insert_cmd();
		task_index insert_index();

		std::string select_cmd();
		task_index select_index();

		std::string change_state_cmd();
		task_index change_state_index();

		std::string delete_done_cmd();
		task_index delete_done_index();
	}
}


class md::model::dal::sqlite::task_index
{
public:
	int card_id() const { return m_card_id; }
	int deck_id() const { return m_deck_id; }
	int state()   const { return m_state; }

	void set_card_id(int ind) { m_card_id = ind; }
	void set_deck_id(int ind) { m_deck_id = ind; }
	void set_state(int ind)   { m_state = ind; }
protected:
	int m_card_id = 0;
	int m_deck_id = 0;
	int m_state = 0;
};


#endif // MEMEDAR_MODEL_DAL_TASK_MAPPER_RESOURCES_HPP
