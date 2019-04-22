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


#ifndef MEMEDAR_MODEL_IDENTITY_HPP
#define MEMEDAR_MODEL_IDENTITY_HPP


namespace md::model {
	class identity;
}


class md::model::identity
{
public:
	explicit identity(std::int64_t id = 0) : m_id {id} { ;}
	std::int64_t id() const { return m_id; }
protected:
	std::int64_t m_id;
};


#endif // MEMEDAR_MODEL_IDENTITY_HPP
