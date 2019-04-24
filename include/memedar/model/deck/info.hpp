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


#ifndef MEMEDAR_MODEL_DECK_INFO_HPP
#define MEMEDAR_MODEL_DECK_INFO_HPP


namespace md::model::deck {
	class info;
}


class md::model::deck::info
{
public:
	explicit info(QString&& name);
	info(QString&& name, std::time_t added, std::time_t last_opening);

	info(md::model::deck::info&& other);
	md::model::deck::info& operator=(md::model::deck::info&& other);

	info(const md::model::deck::info& other) = delete;
	md::model::deck::info& operator=(const md::model::deck::info& other) = delete;

	const QString& name() const;

	std::time_t added() const;

	std::time_t last_opening() const;
	void change_last_opening(std::time_t timestamp);
protected:
	QString m_name;
	std::time_t m_added;
	std::time_t m_last_opening;
};


#endif // MEMEDAR_MODEL_DECK_INFO_HPP
