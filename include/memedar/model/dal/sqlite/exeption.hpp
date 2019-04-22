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


#ifndef MEMEDAR_MODEL_DAL_SQLITE_ADAPTER_EXEPTION_HPP
#define MEMEDAR_MODEL_DAL_SQLITE_ADAPTER_EXEPTION_HPP


namespace md::model::dal::sqlite::adapter {

	class sqlite_error_category;
	std::error_category& get_sqlite_category();

	class sqlite_exeption;
}


class md::model::dal::sqlite::adapter::sqlite_error_category
	: public std::error_category
{
public:
	const char* name() const noexcept override;
	std::string message(int ev) const override;
};


class md::model::dal::sqlite::adapter::sqlite_exeption
	: public std::system_error
{
public:
	sqlite_exeption(int code,
	                const char* errmsg,
	                const std::string& fn);
};


#endif // MEMEDAR_MODEL_DAL_SQLITE_ADAPTER_EXEPTION_HPP
