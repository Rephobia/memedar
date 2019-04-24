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

#include <QString>

#include "memedar/model/deck/info.hpp"

using md::model::deck::info;

info::info(QString&& name)
	: m_name         {std::move(name)}
	, m_added        {std::time(nullptr)}
	, m_last_opening {0}
{ ;}

info::info(QString&& name, std::time_t added, std::time_t last_opening)
	: m_name         {std::move(name)}
	, m_added        {added}
	, m_last_opening {last_opening}
{ ;}

info::info(info&& other)
	: m_name         {std::move(other.m_name)}
	, m_added        {other.m_added}
	, m_last_opening {other.m_last_opening}
{ ;}

info& info::operator=(info&& other)
{
	if (this != &other) {
		m_name = std::move(other.m_name);
		m_added = other.m_added;
		m_last_opening = other.m_last_opening;
	}

	return *this;
}

const QString& info::name() const
{
	return m_name;
}

std::time_t info::added() const
{
	return m_added;
}

std::time_t info::last_opening() const
{
	return m_last_opening;
}

void info::change_last_opening(std::time_t timestamp)
{
	m_last_opening = timestamp;
}
