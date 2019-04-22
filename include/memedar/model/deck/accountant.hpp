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


#ifndef MEMEDAR_MODEL_DECK_ACCOUNTANT_HPP
#define MEMEDAR_MODEL_DECK_ACCOUNTANT_HPP


namespace md::model::card {
	class card;

	class noob_t;
	class ready_t;
	class delayed_t;
}

namespace md::model::deck {
	class accountant;
}


class md::model::deck::accountant
{
public:
	accountant();
	accountant(std::int64_t noob_count, std::int64_t ready_count,
	           std::int64_t delayed_count);

	accountant(md::model::deck::accountant&& other);
	accountant(const md::model::deck::accountant& other) = delete;

	md::model::deck::accountant& operator=(md::model::deck::accountant&& other);
	md::model::deck::accountant& operator=(const md::model::deck::accountant&& other) = delete;

	void process_card(md::model::card::card& card);

	std::int64_t noob_cards(bool is_deck_loaded) const;
	std::int64_t ready_cards(bool is_deck_loaded) const;
	std::int64_t delayed_cards(bool is_deck_loaded) const;
	std::int64_t total_cards(bool is_deck_loaded) const;
protected:
	std::shared_ptr<md::model::card::noob_t> m_noob;
	std::shared_ptr<md::model::card::ready_t> m_ready;
	std::shared_ptr<md::model::card::delayed_t> m_delayed;

	std::int64_t m_noob_db;
	std::int64_t m_ready_db;
	std::int64_t m_delayed_db;
};


#endif // MEMEDAR_MODEL_DECK_ACCOUNTANT_HPP
