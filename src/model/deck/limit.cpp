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


#include <cstdint>

#include "memedar/model/deck/limit.hpp"

using md::model::deck::limit;

limit::limit(std::int64_t max_noob, std::int64_t max_ready,
             std::int64_t daily_noob, std::int64_t daily_ready)
	: m_max_noob    {max_noob}
	, m_max_ready   {max_ready}
	, m_daily_noob  {daily_noob}
	, m_daily_ready {daily_ready}
{ ;}

std::int64_t limit::max_noob_cards() const
{
	return m_max_noob;
}

std::int64_t limit::max_ready_cards() const
{
	return m_max_ready;
}

std::int64_t limit::daily_noob_cards() const
{
	return m_daily_noob;
}

std::int64_t limit::daily_ready_cards() const
{
	return m_daily_ready;
}

void limit::decrement_daily_noob()
{
	--m_daily_noob;
}

void limit::decrement_daily_ready()
{
	--m_daily_ready;
}

void limit::reset_daily()
{
	m_daily_noob = m_max_noob;
	m_daily_ready = m_max_ready;
}
