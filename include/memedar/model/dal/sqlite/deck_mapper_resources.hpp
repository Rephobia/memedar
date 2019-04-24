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


#ifndef MEMEDAR_MODEL_DAL_DECK_MAPPER_RESOURCES_HPP
#define MEMEDAR_MODEL_DAL_DECK_MAPPER_RESOURCES_HPP


namespace md::model::dal::sqlite {
	class deck_index;
	namespace deck_resources {

		std::string create_cmd();

		std::string insert_cmd();
		deck_index insert_index();

		std::string select_cmd();
		deck_index select_index();

		std::string decrement_daily_noob_cmd();
		std::string decrement_daily_ready_cmd();
		deck_index decrement_daily_index();

		std::string update_opening_cmd();
		deck_index update_opening_index();

		std::string reset_daily_cmd();
		deck_index reset_daily_index();
	}
}


class md::model::dal::sqlite::deck_index
{
public:
	int id() const       { return m_id; }
	void set_id(int ind) { m_id = ind; }

	int name() const               { return m_name; }
	int added() const              { return m_added; }
	int last_opening() const       { return m_last_opening; }
	void set_name(int ind)         { m_name = ind; }
	void set_added(int ind)        { m_added = ind; }
	void set_last_opening(int ind) { m_last_opening = ind; }

	int max_noob_cards() const          { return m_max_noob_cards; }
	int max_ready_cards() const         { return m_max_ready_cards; }
	int daily_noob_cards() const        { return m_daily_noob_cards; }
	int daily_ready_cards() const       { return m_daily_ready_cards; }
	void set_max_noob_cards(int ind)    { m_max_noob_cards = ind; }
	void set_max_ready_cards(int ind)   { m_max_ready_cards = ind; }
	void set_daily_noob_cards(int ind)  { m_daily_noob_cards = ind; }
	void set_daily_ready_cards(int ind) { m_daily_ready_cards = ind; }

	int good_gap() const         { return m_good_gap; }
	int easy_gap() const         { return m_easy_gap; }
	int good_ratio() const       { return m_good_ratio; }
	int easy_ratio() const       { return m_easy_ratio; }
	void set_good_gap(int ind)   { m_good_gap = ind; }
	void set_easy_gap(int ind)   { m_easy_gap = ind; }
	void set_good_ratio(int ind) { m_good_ratio = ind; }
	void set_easy_ratio(int ind) { m_easy_ratio = ind; }

	int noob_cards() const          { return m_noob_cards; }
	int ready_cards() const         { return m_ready_cards; }
	int delayed_cards() const       { return m_delayed_cards; }
	int timestamp() const           { return m_timestamp; }
	void set_noob_cards(int ind)    { m_noob_cards = ind; }
	void set_ready_cards(int ind)   { m_ready_cards = ind; }
	void set_delayed_cards(int ind) { m_delayed_cards = ind; }
	void set_timestamp(int ind)     { m_timestamp = ind; }
protected:
	int m_id = 0;

	int m_name = 0;
	int m_added = 0;
	int m_last_opening = 0;

	int m_max_noob_cards = 0;
	int m_max_ready_cards = 0;
	int m_daily_noob_cards = 0;
	int m_daily_ready_cards = 0;

	int m_good_gap = 0;
	int m_easy_gap = 0;
	int m_good_ratio = 0;
	int m_easy_ratio = 0;

	int m_noob_cards = 0;
	int m_ready_cards = 0;
	int m_delayed_cards = 0;
	int m_timestamp = 0;
};


#endif // MEMEDAR_MODEL_DAL_DECK_MAPPER_RESOURCES_HPP
