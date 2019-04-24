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


#include <system_error>

#include <sqlite3.h>

#include "memedar/model/dal/sqlite/exeption.hpp"


using md::model::dal::sqlite::adapter::sqlite_error_category;

const char* sqlite_error_category::name() const noexcept
{
	return "sqlite3";
}

std::string sqlite_error_category::message(int ev) const
{
	if (const char* errorString {::sqlite3_errstr(ev)}) {
		return errorString;
	}
	return "unknown sqlite3 error";
}

std::error_category& md::model::dal::sqlite::adapter::get_sqlite_category()
{
	static sqlite_error_category s_category;
	return s_category;
}

using md::model::dal::sqlite::adapter::sqlite_exeption;

sqlite_exeption::sqlite_exeption(int code,
                                 const char* errmsg,
                                 const std::string& fn)
	: std::system_error {code, get_sqlite_category(),
	                     errmsg + std::string{" when calling "} + fn}
{ ;}
