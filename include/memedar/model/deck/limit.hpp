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


#ifndef MEMEDAR_MODEL_DECK_LIMIT_HPP
#define MEMEDAR_MODEL_DECK_LIMIT_HPP


namespace md::model::deck {
	class limit;
}


class md::model::deck::limit
{
public:
	limit() = default;
	limit(std::int64_t max_noob, std::int64_t max_ready,
	      std::int64_t daily_noob, std::int64_t daily_ready);

	std::int64_t max_noob_cards() const;
	std::int64_t max_ready_cards() const;
	std::int64_t daily_noob_cards() const;
	std::int64_t daily_ready_cards() const;

	void decrement_daily_noob();
	void decrement_daily_ready();
	void reset_daily();
private:
	enum : int { DEFAULT_MAX = 100000 };

	std::int64_t m_max_noob = DEFAULT_MAX;
	std::int64_t m_max_ready = DEFAULT_MAX;
	std::int64_t m_daily_noob = DEFAULT_MAX;
	std::int64_t m_daily_ready = DEFAULT_MAX;
};


#endif // MEMEDAR_MODEL_DECK_LIMIT_HPP
