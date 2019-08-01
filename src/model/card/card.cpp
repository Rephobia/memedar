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
#include <memory>
#include <functional>

#include <QString>

#include "memedar/model/card/visitor.hpp"
#include "memedar/model/card/type.hpp"
#include "memedar/model/card/card.hpp"


using md::model::card::card_value;

card_value::card_value(bool typing)
	: card::schedule {schedule {}}
	, card::combo    {combo {}}
	, has_typing     {typing}
{ ;}

card_value::card_value(card::schedule schedule,
                       card::combo combo,
                       bool typing)
	: card::schedule {schedule}
	, card::combo    {combo}
	, has_typing     {typing}
{ ;}

using md::model::card::card;

card::card(identity id,
           card::card_value card_value,
           side::side&& question_side,
           side::side&& answer_side)
	: identity         {id}
	, card::card_value {card_value}
	, question         {std::move(question_side)}
	, answer           {std::move(answer_side)}
	, m_type           {nullptr}
{ ;}

void card::set_type(std::shared_ptr<md::model::card::type> type)
{
	m_type = type;
}

void card::visit(std::function<void(noob_t&)>&& noob,
                 std::function<void(ready_t&)>&& ready,
                 std::function<void(delayed_t&)>&& delayed)
{
	md::model::card::visitor visitor {std::move(noob),
	                                  std::move(ready),
	                                  std::move(delayed)};
	m_type->accept(visitor);
}
