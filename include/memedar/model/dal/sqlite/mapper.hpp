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


#ifndef MEMEDAR_MODEL_DAL_SQLITE_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_SQLITE_MAPPER_HPP


namespace md::model::dal {
	class transaction;
	class card_mapper;
	class deck_mapper;
	class task_mapper;
}

namespace md::model::dal::sqlite {
	class mapper;
}


class md::model::dal::sqlite::mapper : public md::model::dal::mapper
{
public:
	explicit mapper(md::model::dal::sqlite::adapter::handle& db);
	
	md::model::dal::transaction_guard make_transaction() override;	
	void save_card(md::model::deck::deck& deck,
	               md::model::task::task_book& task_book,
	               md::model::card::card_dto&& new_card) override;
	void reset_task(md::model::task::task& task) override;
	
	void save_deck(std::deque<md::model::deck::deck>& decks,
                       md::model::deck::deck_value&& deck_value) override;
	std::deque<md::model::deck::deck> load_decks() override;

	void update_side(md::model::side::side& old_side,
	                 md::model::side::side_value&& new_side) override;
	
	void update_card(md::model::card::card& card, bool typing) override;
		
	md::model::task::task_book make_task_book(md::model::deck::deck& deck) override;	
	void done_noob(md::model::deck::deck& deck,
	               md::model::task::task& task, std::time_t gap) override;
	void done_ready(md::model::deck::deck& deck,
	                md::model::task::task& task, std::time_t gap) override;
	~mapper() override;
protected:
	void fill_from_deck(md::model::deck::deck& deck, md::model::task::task_book& task_book);
protected:
	std::unique_ptr<md::model::dal::transaction> m_transaction;
	std::unique_ptr<md::model::dal::card_mapper> m_card_mapper;
	std::unique_ptr<md::model::dal::deck_mapper> m_deck_mapper;
	std::unique_ptr<md::model::dal::task_mapper> m_task_mapper;
};


#endif // MEMEDAR_MODEL_DAL_SQLITE_MAPPER_HPP
