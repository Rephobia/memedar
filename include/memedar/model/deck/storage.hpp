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


#ifndef MEMEDAR_MODEL_DECK_STORAGE_HPP
#define MEMEDAR_MODEL_DECK_STORAGE_HPP


#include <memory>
#include <boost/signals2.hpp>

#include "memedar/utils/storage.hpp"


namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
	class deck_storage;
}


class md::model::deck::deck_storage
	: protected md::utils::storage<std::shared_ptr<md::model::card::card>>
{
public:
	deck_storage();

	deck_storage(md::model::deck::deck_storage&& other);

	md::model::deck::deck_storage& operator=(md::model::deck::deck_storage&& other);
	
	boost::signals2::signal<void(md::model::deck::deck& deck)> need_cards {};
	boost::signals2::signal<void(md::model::deck::deck& deck,
	                             std::shared_ptr<md::model::card::card>)> card_added {};

	bool is_empty() const;
	bool is_loaded() const;
	
	class boss;
	friend class boss;
	// cppcheck-suppress functionConst
	md::model::deck::deck_storage::boss get_storage_boss();
private:
	enum class status : int {empty, loading, loaded};
	md::model::deck::deck_storage::status m_status;

	void set_status(md::model::deck::deck_storage::status status);
};


class md::model::deck::deck_storage::boss
{
public:
	explicit boss(md::model::deck::deck_storage& deck_storage);
	void commit();
	~boss();
protected:
	bool m_commit;
	md::model::deck::deck_storage& m_storage;
};


#endif // MEMEDAR_MODEL_DECK_STORAGE_HPP
