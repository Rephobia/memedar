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


#include <cassert>

#include <ctime>
#include <algorithm>

#include "memedar/model/deck/gap.hpp"
#include "memedar/model/card/combo.hpp"


using md::model::card::combo;

combo::combo(int value)
	: m_combo {std::min(value, MAX_COMBO)}
{
	assert(m_combo >= MIN_COMBO && "combo isn't valid");
}

int combo::get_combo() const
{
	return m_combo;
}

void combo::increment_combo()
{
	m_combo = std::min(m_combo + 1, MAX_COMBO);
}

void combo::reset_combo()
{
	m_combo = MIN_COMBO;
}

std::time_t combo::interval(md::model::deck::gap gap) const
{
	return gap.brutto_value() * m_combo - gap.brutto_value()
		+ gap.netto_value();
}
