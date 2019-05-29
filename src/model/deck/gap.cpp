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


#include <ctime>

#include "memedar/utils/time.hpp"
#include "memedar/utils/constants.hpp"
#include "memedar/model/deck/gap.hpp"


using md::model::deck::gap;

gap::gap(std::time_t gap_value, int gap_ratio)
	: m_value {gap_value}
	, m_ratio {gap_ratio}
{ ;}

std::time_t gap::netto_value() const
{
	return m_value;
}

std::time_t gap::brutto_value() const
{
	return m_value/utils::constants::PTC_100 * m_ratio;
}

int gap::ratio() const
{
	return m_ratio;
}


using md::model::deck::gaps;

gaps::gaps()
	: m_good_gap {utils::time::DAY, utils::constants::PTC_100}
	, m_easy_gap {utils::time::DAY * 3, utils::constants::PTC_200}
{ ;}

gaps::gaps(gap good_gap, gap easy_gap)
	: m_good_gap {good_gap}
	, m_easy_gap {easy_gap}
{ ;}

gap gaps::good_gap() const
{
	return m_good_gap;
}

gap gaps::easy_gap() const
{
	return m_easy_gap;
}
