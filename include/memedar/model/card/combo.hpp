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


#ifndef MEMEDAR_MODEL_CARD_COMBO_HPP
#define MEMEDAR_MODEL_CARD_COMBO_HPP


namespace md::model::card {
	class combo;
}

namespace md::model::deck {
	class gap;
}


class md::model::card::combo
{
public:
	static constexpr int WITHOUT_COMBO {1};
	static constexpr int MAX_COMBO {600};

	explicit combo(int value = WITHOUT_COMBO);

	int get_combo() const;
	std::time_t interval(md::model::deck::gap gap) const;

	void increment_combo();
	void reset_combo();
private:
	int m_combo;

};


#endif // MEMEDAR_MODEL_CARD_COMBO_HPP
