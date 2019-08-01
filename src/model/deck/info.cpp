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


#include <QString>

#include "memedar/model/deck/info.hpp"


using md::model::deck::info;

info::info(QString&& name)
	: m_name {std::move(name)}
{ ;}

info::info(info&& other)
	: m_name {std::move(other.m_name)}

{ ;}

info& info::operator=(info&& other)
{
	if (this != &other) {
		m_name = std::move(other.m_name);
	}

	return *this;
}

const QString& info::name() const
{
	return m_name;
}
