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


#include <ctime>
#include <algorithm>

#include "memedar/utils/constants.hpp"
#include "memedar/model/card/schedule.hpp"
#include "memedar/model/deck/gap.hpp"

using md::model::card::combo;

combo::combo(int value)
	: m_value {std::clamp(value, MIN_COMBO, MAX_COMBO)}
{ ;}

combo::operator int() const
{
	return m_value;
}

combo& combo::operator++()
{
	++m_value;
	return *this;
}

int operator*(const int lhs, const combo rhs)
{
	return lhs * rhs.m_value;
}

int operator*(const combo lhs, const int rhs)
{
	return lhs.m_value * rhs;
}


using md::model::card::schedule;

schedule::schedule()
	: m_added  {std::time(nullptr)}
	, m_repeat {0}
	, m_combo  {card::combo {}}
{ ;}

schedule::schedule(std::time_t added, std::time_t repeat, card::combo combo)
	: m_added  {added}
	, m_repeat {repeat}
	, m_combo  {combo}
{ ;}

std::time_t schedule::added() const
{
	return m_added;
}

std::time_t schedule::repeat() const
{
	return m_repeat;
}

void schedule::change_repeat(std::time_t val)
{
	m_repeat = val;
}

combo schedule::combo() const
{
	return m_combo;
}

void schedule::increment_combo()
{
	++m_combo;
}

void schedule::reset_combo()
{
	m_combo = card::combo {};
}

std::time_t schedule::interval(md::model::deck::gap gap) const
{
	return gap.value/utils::constants::PTC_100 * gap.ratio * m_combo
		+ gap.value
		- gap.value/utils::constants::PTC_100 * gap.ratio;
}
