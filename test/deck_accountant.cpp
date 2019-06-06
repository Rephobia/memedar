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

#include <catch2/catch.hpp>

#include "memedar/model/deck/accountant.hpp"


using md::model::deck::accountant;


TEST_CASE("result of accountant counts if database didn't load", "[deck][accountant]")
{	
	std::int64_t noob_count {10};
	std::int64_t ready_count {13};
	std::int64_t delayed_count {29};

	accountant accountant {noob_count, ready_count, delayed_count};

	bool not_loaded {false};
	
	REQUIRE(accountant.noob_cards(not_loaded) == noob_count);
	REQUIRE(accountant.ready_cards(not_loaded) == ready_count);
	REQUIRE(accountant.delayed_cards(not_loaded) == delayed_count);
	REQUIRE(accountant.total_cards(not_loaded) == noob_count
	        + ready_count + delayed_count);		
}

