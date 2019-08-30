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


#ifndef MEMEDAR_MODEL_DECK_DECK_HPP
#define MEMEDAR_MODEL_DECK_DECK_HPP


#include <QString>

#include "memedar/model/identity.hpp"
#include "memedar/model/deck/time.hpp"
#include "memedar/model/deck/gap.hpp"
#include "memedar/model/deck/limit.hpp"
#include "memedar/model/deck/accountant.hpp"
#include "memedar/model/deck/storage.hpp"


namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck_value;
	class deck;
}


class md::model::deck::deck_value : public md::model::deck::time
                                  , public md::model::deck::limit
                                  , public md::model::deck::gaps
{
public:
	explicit deck_value(QString&& name);
	
	deck_value(QString&& name,
	           md::model::deck::time time,
	           md::model::deck::limit limit,
	           md::model::deck::gaps gaps);
	
	explicit deck_value(md::model::deck::deck_value&& other);
	deck_value(const md::model::deck::deck_value& other) = delete;

	md::model::deck::deck_value& operator=(md::model::deck::deck_value&& other);
	md::model::deck::deck_value& operator=(const md::model::deck::deck_value& other) = delete;

	const QString& name() const;
	QString& name();
	void change_name(QString&& name);
protected:
	QString m_name;
};


class md::model::deck::deck : public md::model::identity
                            , public md::model::deck::deck_value
                            , public md::model::deck::deck_storage
{
public:
	deck(md::model::identity id,
	     md::model::deck::deck_value&& deck_value);
	
	deck(md::model::identity id,
	     md::model::deck::deck_value&& deck_value,
	     md::model::deck::accountant&& accountant);
	
	std::int64_t noob_cards() const;
	std::int64_t ready_cards() const;
	std::int64_t delayed_cards() const;
	std::int64_t total_cards() const;

	void process_card(md::model::card::card& card);

	md::utils::storage<std::shared_ptr<md::model::card::card>>& cards();

	void add_card(md::model::card::card&& card);
protected:
	md::model::deck::accountant m_accountant {};
};


#endif // MEMEDAR_MODEL_DECK_DECK_HPP
