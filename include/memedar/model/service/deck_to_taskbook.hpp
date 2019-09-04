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


#ifndef MEMEDAR_MODEL_DECK_TO_TASKBOOK_HPP
#define MEMEDAR_MODEL_DECK_TO_TASKBOOK_HPP


#include <map>
#include <deque>


namespace md::model {
	class deck_to_taskbook_detail;
	class deck_to_taskbook;
}

namespace md::model::dal {
	class mapper;
}


class md::model::deck_to_taskbook_detail
{
public:
	void add_deck(md::model::deck::deck&& deck);
	void delete_deck(md::model::deck::deck& deck);
	void delete_card(md::model::deck::deck& deck, md::model::card::card& card);
	
	using iterator = std::map<md::model::identity,
	                          md::model::task::taskbook>::iterator;
	iterator begin();
	iterator end();
	
	std::deque<md::model::deck::deck>& get_decks();
	iterator get_taskbook(md::model::deck::deck& deck);
	
	iterator add_taskbook(md::model::deck::deck& deck,
	                      md::model::task::taskbook&& taskbook);
private:
	std::deque<md::model::deck::deck> m_decks {};
	std::map<md::model::identity, md::model::task::taskbook> m_tasks {};	
};


class md::model::deck_to_taskbook
{
public:
	explicit deck_to_taskbook(md::model::dal::mapper& mapper);
		
	md::model::task::taskbook& get_taskbook(md::model::deck::deck& deck);
	std::deque<md::model::deck::deck>& get_decks();
protected:
	void add_deck(md::model::deck::deck&& deck);
	void delete_deck(md::model::deck::deck& deck);
	void delete_card(md::model::deck::deck& deck, md::model::card::card& card);
	
	md::model::task::taskbook make_taskbook(md::model::deck::deck& deck);
	std::optional<md::model::task::task*> get_task(md::model::deck::deck& deck,
	                                               md::model::card::card& card);
private:
	std::deque<md::model::deck::deck> load_decks();
	void fill_from_deck(md::model::deck::deck& deck,
	                    md::model::task::taskbook& taskbook);
private:
	bool m_decks_loaded {false};
	md::model::deck_to_taskbook_detail m_storage {};
	md::model::dal::mapper& m_mapper;
};


#endif // MEMEDAR_MODEL_DECK_TO_TASKBOOK_HPP
