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

#include "memedar/model/card/schedule.hpp"


using md::model::card::schedule;

schedule::schedule()
	: m_added  {std::time(nullptr)}
	, m_repeat {0}
{ ;}

schedule::schedule(std::time_t added, std::time_t repeat)
	: m_added  {added}
	, m_repeat {repeat}
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
