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


#ifndef MEMEDAR_MODEL_SIDE_SIDE_HPP
#define MEMEDAR_MODEL_SIDE_SIDE_HPP


#include <QString>

#include "memedar/model/identity.hpp"


namespace md::model::side {
	class side;
	class side_value;
}


class md::model::side::side_value
{
public:
	explicit side_value(QString&& text);
	explicit side_value(md::model::side::side_value&& other);
	side_value(const md::model::side::side_value& other) = delete;

	md::model::side::side_value& operator=(md::model::side::side_value&& other);
	md::model::side::side_value& operator=(const md::model::side::side_value& other) = delete;
	
	const QString& text() const;
protected:
	QString m_text;
};


class md::model::side::side : public md::model::identity
                            , public md::model::side::side_value
{
public:
	side(md::model::identity id, md::model::side::side_value&& value);
	
	md::model::side::side& operator=(md::model::side::side_value&& value);
};


#endif // MEMEDAR_MODEL_SIDE_SIDE_HPP
