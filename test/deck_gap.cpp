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

#include <catch2/catch.hpp>

#include "memedar/utils/time.hpp"
#include "memedar/utils/constant.hpp"
#include "memedar/model/deck/gap.hpp"


using md::model::deck::gap;
using namespace md::utils;


TEST_CASE("deck::gap calculates brutto correctly", "[deck][gap]")
{	
	std::time_t value {time::DAY};
	int ratio {constant::PTC_50};
	gap gap {value, ratio};
	
	REQUIRE(gap.brutto_value() == value / constant::PTC_100 * ratio);
}
