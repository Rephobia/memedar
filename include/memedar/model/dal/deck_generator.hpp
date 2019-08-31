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


#ifndef MEMEDAR_MODEL_DAL_DECK_GENERATOR_HPP
#define MEMEDAR_MODEL_DAL_DECK_GENERATOR_HPP


#include <optional>

namespace md::model::deck {
	class deck;
}

namespace md::model::dal {
	class deck_generator;
}


class md::model::dal::deck_generator
{
public:
	virtual std::optional<md::model::deck::deck> get_deck() = 0;

	virtual ~deck_generator() = default;
};


#endif // MEMEDAR_MODEL_DAL_DECK_GENERATOR_HPP
