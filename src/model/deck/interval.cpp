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

#include "memedar/utils/time.hpp"
#include "memedar/utils/constants.hpp"
#include "memedar/model/card/schedule.hpp"
#include "memedar/model/deck/interval.hpp"


using md::model::deck::gap_ratio;
using md::model::deck::interval;

interval::interval()
	: m_good_gap   {utils::time::DAY}
	, m_easy_gap   {utils::time::DAY * 3}
	, m_good_ratio {utils::constants::PTC_100}
	, m_easy_ratio {utils::constants::PTC_200}
{ ;}

interval::interval(std::time_t good_gap, std::time_t easy_gap,
                   gap_ratio good_ratio,
                   gap_ratio easy_ratio)
	: m_good_gap   {good_gap}
	, m_easy_gap   {easy_gap}
	, m_good_ratio {good_ratio}
	, m_easy_ratio {easy_ratio}
{ ;}

std::time_t interval::good_interval(card::combo combo) const
{
	return calculate_interval(m_good_gap, m_good_ratio, combo);
}

std::time_t  interval::easy_interval(card::combo combo) const
{
	return calculate_interval(m_easy_gap, m_easy_ratio, combo);
}

std::time_t interval::calculate_interval(std::time_t gap,
                                         gap_ratio ratio,
                                         card::combo combo) const
{
	return gap/utils::constants::PTC_100 * ratio * combo
		+ gap
		- gap/utils::constants::PTC_100 * ratio;
}

std::time_t interval::good_gap() const
{
	return m_good_gap;
}

std::time_t interval::easy_gap() const
{
	return m_easy_gap;
}

gap_ratio interval::good_ratio() const
{
	return m_good_ratio;
}

gap_ratio interval::easy_ratio() const
{
	return m_easy_ratio;
}
