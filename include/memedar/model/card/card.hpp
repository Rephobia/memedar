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


#ifndef MEMEDAR_MODEL_CARD_CARD_HPP
#define MEMEDAR_MODEL_CARD_CARD_HPP


#include <functional>
#include <memory>

#include "memedar/model/identity.hpp"
#include "memedar/model/side/side.hpp"
#include "memedar/model/card/schedule.hpp"
#include "memedar/model/card/combo.hpp"


namespace md::model::card {
	class type;

	struct noob_t;
	struct ready_t;
	struct delayed_t;
	
	class card_value;
	class card_dto;
	class card;
}


class md::model::card::card_value : public md::model::card::schedule
                                  , public md::model::card::combo
{
public:
	explicit card_value(bool typing);
	card_value(md::model::card::schedule schedule,
	           md::model::card::combo combo,
	           bool typing);

	bool has_typing;
};


class md::model::card::card_dto
{
public:
	card_dto(md::model::card::card_value card_value,
	         md::model::side::side_value&& question_value,
	         md::model::side::side_value&& answer_value)
		: value    {card_value}
		, question {std::move(question_value)}
		, answer   {std::move(answer_value)}
	{ ;}
	md::model::card::card_value value;
	md::model::side::side_value question;
	md::model::side::side_value answer;
};


class md::model::card::card : public md::model::identity
                            , public md::model::card::card_value
{
public:
	card(md::model::identity id,
	     md::model::card::card_value card_value,
	     md::model::side::side&& question,
	     md::model::side::side&& answer);
	
	md::model::side::side question;
	md::model::side::side answer;
		
	void set_type(std::shared_ptr<md::model::card::type> type);

	void visit(std::function<void(md::model::card::noob_t&)>&& noob,
	           std::function<void(md::model::card::ready_t&)>&& ready,
	           std::function<void(md::model::card::delayed_t&)>&& delayed
	           = [](md::model::card::delayed_t&){});
protected:
	std::shared_ptr<md::model::card::type> m_type;
};


#endif // MEMEDAR_MODEL_CARD_CARD_HPP
