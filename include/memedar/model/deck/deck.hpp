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


#ifndef MEMEDAR_MODEL_DECK_DECK_HPP
#define MEMEDAR_MODEL_DECK_DECK_HPP


#include "memedar/model/identity.hpp"
#include "memedar/model/deck/info.hpp"
#include "memedar/model/deck/interval.hpp"
#include "memedar/model/deck/accountant.hpp"
#include "memedar/model/deck/limit.hpp"


namespace md::utils {
	template<class T>
	class storage;
}

namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
}


class md::model::deck::deck : public md::model::identity
                            , public md::model::deck::info
                            , public md::model::deck::limit
                            , public md::model::deck::interval
                            , public md::utils::storage<md::model::card::card>
{
public:
	explicit deck(md::model::deck::info&& info);

	deck(md::model::identity id,
	     md::model::deck::info&& info,
	     md::model::deck::limit limit,
	     md::model::deck::interval interval,
	     md::model::deck::accountant&& accountant);

	std::int64_t noob_cards() const;
	std::int64_t ready_cards() const;
	std::int64_t delayed_cards() const;
	std::int64_t total_cards() const;

	void process_card(md::model::card::card& card);
	void add_card(md::model::card::card&& card);
protected:
	md::model::deck::accountant m_accountant;
private:
	using storage::add;
};


#endif // MEMEDAR_MODEL_DECK_DECK_HPP
