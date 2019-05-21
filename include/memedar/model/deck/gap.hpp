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


#ifndef MEMEDAR_MODEL_DECK_GAP_HPP
#define MEMEDAR_MODEL_DECK_GAP_HPP


namespace md::model::deck {
	using gap_ratio = unsigned int;
	class gap;
	class gaps;
}


class md::model::deck::gap
{
public:
	gap(std::time_t gap_value, md::model::deck::gap_ratio gap_ratio);

	std::time_t value;
	std::time_t ratio;
};


class md::model::deck::gaps
{
public:
	gaps();
	gaps(md::model::deck::gap good_gap,
	     md::model::deck::gap easy_gap);

	md::model::deck::gap good_gap() const;
	md::model::deck::gap easy_gap() const;
protected:
	md::model::deck::gap m_good_gap;
	md::model::deck::gap m_easy_gap;
};


#endif // MEMEDAR_MODEL_DECK_GAP_HPP
