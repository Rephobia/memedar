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
#include "memedar/model/card/combo.hpp"
#include "memedar/model/deck/gap.hpp"


TEST_CASE("card interval equal gap value without combo", "[card][combo]")
{
	using md::model::card::combo;
	using md::model::deck::gap;

	combo combo {combo::WITHOUT_COMBO};

	std::time_t value {md::utils::time::DAY};
	
	gap gap50  {value, md::utils::constant::PTC_50};
	gap gap100 {value, md::utils::constant::PTC_100};
	gap gap200 {value, md::utils::constant::PTC_200};
	
	REQUIRE(combo.interval(gap50) == value);
	REQUIRE(combo.interval(gap100) == value);
	REQUIRE(combo.interval(gap200) == value);
}
