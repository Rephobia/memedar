/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov (Linhurdos) <teremdev@gmail.com>

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


#include <functional>

#include "memedar/model/card/visitor.hpp"


using namespace  md::model::card;

visitor::visitor(std::function<void(noob_t&)>&& noob,
                 std::function<void(ready_t&)>&& ready,
                 std::function<void(delayed_t&)>&& delayed)
	: m_noob    {std::move(noob)}
	, m_ready   {std::move(ready)}
	, m_delayed {std::move(delayed)}
{ ;}

void visitor::visit(md::model::card::noob_t& ref)
{
	m_noob(ref);
}

void visitor::visit(md::model::card::ready_t& ref)
{
	m_ready(ref);
}

void visitor::visit(md::model::card::delayed_t& ref)
{
	m_delayed(ref);
}
