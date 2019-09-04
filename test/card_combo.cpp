/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2018-2019 Roman Erdyakov

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

#include <catch2/catch.hpp>

#include "memedar/utils/time.hpp"
#include "memedar/utils/constant.hpp"
#include "memedar/model/card/combo.hpp"
#include "memedar/model/deck/gap.hpp"


using md::model::card::combo;
using md::model::deck::gap;
using namespace md::utils;


TEST_CASE("card interval without combo equals gap value", "[card][combo][interval]")
{
	combo combo {combo::WITHOUT_COMBO};

	std::time_t value {time::DAY};
	
	gap gap50  {value, constant::PTC_50};
	gap gap100 {value, constant::PTC_100};
	gap gap200 {value, constant::PTC_200};
	
	REQUIRE(combo.interval(gap50) == value);
	REQUIRE(combo.interval(gap100) == value);
	REQUIRE(combo.interval(gap200) == value);
}


TEST_CASE("card interval is gaining combo correctly", "[card][combo][interval]")
{
	combo combo {10};

	std::time_t value {time::DAY};
	int gap_ratio {constant::PTC_50};
	gap gap {value, gap_ratio};

	std::time_t correct_answer {gap.brutto_value() * combo.get_combo()
	                            - gap.brutto_value()
	                            + value};
	
	REQUIRE(combo.interval(gap) == correct_answer);
}
