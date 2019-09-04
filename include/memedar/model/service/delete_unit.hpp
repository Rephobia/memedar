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

#ifndef MEMEDAR_MODEL_DELETE_UNIT_HPP
#define MEMEDAR_MODEL_DELETE_UNIT_HPP


#include "memedar/model/service/deck_to_taskbook.hpp"


namespace md::model {
	class delete_unit;
}


class md::model::delete_unit : private virtual md::model::deck_to_taskbook
{
public:
	explicit delete_unit(md::model::dal::mapper& mapper);
	void delete_deck(md::model::deck::deck& deck);
	void delete_card(md::model::deck::deck& deck, md::model::card::card& card);
private:	
	md::model::dal::mapper& m_mapper;
};


#endif // MEMEDAR_MODEL_DELETE_UNIT_HPP
