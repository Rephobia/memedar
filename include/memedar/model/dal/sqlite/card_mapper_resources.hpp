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


#ifndef MEMEDAR_MODEL_DAL_CARD_MAPPER_RESOURCES_HPP
#define MEMEDAR_MODEL_DAL_CARD_MAPPER_RESOURCES_HPP


namespace md::model::dal::sqlite {
	class side_index;
	class card_index;

	namespace card_resources {

		std::string create_cmd();
		std::string create_side_cmd();

		std::string insert_cmd();
		card_index insert_index();

		std::string insert_side_cmd();
		side_index insert_side_index();

		std::string select_cmd();
		card_index select_index();
		
		std::string update_side_cmd();
		side_index update_side_index();
	
		std::string update_repeat_cmd();
		card_index update_repeat_index();

		std::string reset_combo_cmd();
		card_index reset_combo_index();
	}
}


class md::model::dal::sqlite::side_index
{
public:
	int id() const       { return m_id; }
	void set_id(int ind) { m_id = ind; }

	int text() const       { return m_text; }
	void set_text(int ind) { m_text = ind; }
protected:
	int m_id = 0;
	int m_text = 0;
};


class md::model::dal::sqlite::card_index
{
public:
	int id() const       { return m_id; }
	void set_id(int ind) {  m_id = ind; }

	int deck_id() const       { return m_deck_id; }
	void set_deck_id(int ind) {  m_deck_id = ind; }

	int added() const        { return m_added; }
	int repeat() const       { return m_repeat; }
	int combo() const        { return m_combo; }
	void set_added(int ind)  {  m_added = ind; }
	void set_repeat(int ind) {  m_repeat = ind; }
	void set_combo(int ind)  {  m_combo = ind; }

	int question_id() const       { return m_question_id; }
	int answer_id() const         { return m_answer_id; }
	void set_question_id(int ind) {  m_question_id = ind; }
	void set_answer_id(int ind)   {  m_answer_id = ind; }

	int typing() const       { return m_typing; }
	void set_typing(int ind) {  m_typing = ind; }

	md::model::dal::sqlite::side_index question {md::model::dal::sqlite::side_index {}};
	md::model::dal::sqlite::side_index answer {md::model::dal::sqlite::side_index {}};
protected:
	int m_id = 0;
	int m_deck_id = 0;

	int m_added = 0;
	int m_repeat = 0;
	int m_combo = 0;

	int m_question_id = 0;
	int m_answer_id = 0;

	int m_typing = 0;
};


#endif // MEMEDAR_MODEL_DAL_CARD_MAPPER_RESOURCES_HPP
