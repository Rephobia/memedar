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
	class storage_status;
	class storage_container;
	class storage;
}


class md::model::deck::storage_status
{
public:
	storage_status() = default;
	bool is_empty() const;
	bool is_loaded() const;
protected:
	enum class status : int {empty, loading, loaded};

	void set_status(md::model::deck::storage_status::status status);
private:
	md::model::deck::storage_status::status m_status {status::empty};
};


class md::model::deck::storage_container
{
public:
	storage_container() = default;
	void delete_card(md::model::card::card& card);
protected:
	using shared_card = std::shared_ptr<md::model::card::card>;
	
	void add_card(shared_card card);
	md::utils::storage<shared_card>& cards();
private:
	md::utils::editable_storage<shared_card> m_storage {};
};


class md::model::deck::storage : public md::model::deck::storage_status
                               , public md::model::deck::storage_container
{
public:
	storage() = default;
	storage(md::model::deck::storage&& other);

	md::model::deck::storage& operator=(md::model::deck::storage&& other);
	
	boost::signals2::signal<void(md::model::deck::deck& deck)> need_cards {};
	boost::signals2::signal<void(md::model::deck::deck& deck,
	                             shared_card)> card_added {};
	class boss;
	friend class boss;
	// cppcheck-suppress functionConst
	md::model::deck::storage::boss get_storage_boss();
};


class md::model::deck::storage::boss
{
public:
	explicit boss(md::model::deck::storage& storage);
	void commit();
	~boss();
protected:
	bool m_commit;
	md::model::deck::storage& m_storage;
};


#endif // MEMEDAR_MODEL_DECK_STORAGE_HPP
