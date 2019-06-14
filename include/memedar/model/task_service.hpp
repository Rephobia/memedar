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


#ifndef MEMEDAR_MODEL_TASK_SERVICE_HPP
#define MEMEDAR_MODEL_TASK_SERVICE_HPP


namespace md::model::deck {
	class deck;
}

namespace md::model::task {
	class task;
}

namespace md::model::dal {
	class card_mapper;
	class deck_mapper;
	class task_mapper;
	class transaction;
}

namespace md::view {
	class error_delegate;
}

namespace md::model {
	class task_service;
}


class md::model::task_service
{
public:
	task_service(md::view::error_delegate& error_delegate,
	             md::model::dal::transaction& transaction,
	             md::model::dal::card_mapper& card_mapper,
	             md::model::dal::deck_mapper& deck_mapper,
	             md::model::dal::task_mapper& task_mapper);

	md::model::task::task_book make_task(md::model::deck::deck& deck);
	void update_task_book(md::model::task::task_book& task_book);
	
	void again_card(md::model::task::task& task);
	void done_card(md::model::deck::deck& deck, md::model::task::task& task, std::time_t gap);
protected:
	void fill_from_deck(md::model::task::task_book& task_book);
	class done_visitor;
protected:
	md::view::error_delegate& m_error_delegate;
	md::model::dal::transaction& m_transaction;
	md::model::dal::card_mapper& m_card_mapper;
	md::model::dal::deck_mapper& m_deck_mapper;
	md::model::dal::task_mapper& m_task_mapper;
};


#endif // MEMEDAR_MODEL_TASK_SERVICE_HPP
