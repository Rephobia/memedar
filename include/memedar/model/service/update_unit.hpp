/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov (Linhurdos) <teremdev@gmail.com>

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

#ifndef MEMEDAR_MODEL_UPDATE_UNIT_HPP
#define MEMEDAR_MODEL_UPDATE_UNIT_HPP


namespace md::model::side {
	class side;
	class side_value;
}

namespace md::model {
	class update_unit;
}


class md::model::update_unit
{
public:
	explicit update_unit(md::model::dal::mapper& mapper);
	
	bool update_card(md::model::card::card& card,
	                 md::model::card::card_dto&& new_card);
	void update_task(md::model::task::task& task,
	                 md::model::card::card_dto&& new_card);
	void update_deck(md::model::deck::deck& deck,
	                 md::model::deck::deck_value&& new_deck);
protected:
	void update_side(md::model::side::side& old_side,
	                 md::model::side::side_value&& new_side);
private:
	md::model::dal::mapper& m_mapper;	
};


#endif // MEMEDAR_MODEL_UPDATE_UNIT_HPP
