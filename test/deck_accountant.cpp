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
#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/accountant.hpp"


using namespace md::utils;
using md::model::identity;
using md::model::deck::accountant;
using md::model::side::side_value;
using md::model::side::side;
using md::model::card::card_value;
using md::model::card::card;


TEST_CASE("result of accountant counts if db didn't load", "[deck][accountant]")
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


TEST_CASE("accountant processes card", "[deck][accountant]")
{
	side_value question_value {"q"};
	side_value answer_value {"a"};
	
	side question {identity {1}, std::move(question_value)};
	side answer {identity {2}, std::move(answer_value)};

	bool typing {false};
	card_value card_value {typing};
	
	card card {identity {1}, card_value, std::move(question), std::move(answer)};
	
	accountant accountant {};
	bool loaded {true};
	
	SECTION("process noob card") {
		
		accountant.process_card(card);
		
		REQUIRE(accountant.noob_cards(loaded) == 1);
		REQUIRE(accountant.ready_cards(loaded) == 0);
		REQUIRE(accountant.delayed_cards(loaded) == 0);
		REQUIRE(accountant.total_cards(loaded) == 1);
	}
	
	SECTION("process ready card") {
		
		card.change_repeat(std::time(nullptr) - time::DAY);
		accountant.process_card(card);
		
		REQUIRE(accountant.noob_cards(loaded) == 0);
		REQUIRE(accountant.ready_cards(loaded) == 1);
		REQUIRE(accountant.delayed_cards(loaded) == 0);
		REQUIRE(accountant.total_cards(loaded) == 1);
	}
	
	SECTION("process delayed card") {
		card.change_repeat(std::time(nullptr) + time::DAY);
		accountant.process_card(card);
		
		REQUIRE(accountant.noob_cards(loaded) == 0);
		REQUIRE(accountant.ready_cards(loaded) == 0);
		REQUIRE(accountant.delayed_cards(loaded) == 1);
		REQUIRE(accountant.total_cards(loaded) == 1);
	}
}
