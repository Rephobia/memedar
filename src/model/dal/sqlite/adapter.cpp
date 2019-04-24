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


#include <memory>
#include <filesystem>

#include <sqlite3.h>
#include <QString>

#include "memedar/model/dal/sqlite/exeption.hpp"
#include "memedar/model/dal/sqlite/adapter.hpp"


namespace adapter = md::model::dal::sqlite::adapter;

using md::model::dal::sqlite::adapter::handle;
using md::model::dal::sqlite::adapter::statement;
using md::model::dal::sqlite::adapter::connector;
using md::model::dal::sqlite::adapter::sqlite_exeption;


QString adapter::detail::convert_to_qstring(const unsigned char *str)
{
	return QString::fromUtf8(reinterpret_cast<const char*>(str));
}

handle adapter::open_sqlite(const std::filesystem::path& path)
{
	const std::string pathUtf8 {path.u8string()};

	sqlite3* sqlite_handle {nullptr};
	const int code {::sqlite3_open(pathUtf8.c_str(), &sqlite_handle)};

	adapter::handle handle {sqlite_handle};

	if (code != SQLITE_OK) {

		throw sqlite_exeption {code, ::sqlite3_errmsg(sqlite_handle), "sqlite3_open"};

	}

	return handle;
}

statement adapter::prepare_sqlite(const handle& db, const std::string& sqlCmd)
{
	sqlite3_stmt* sqlite_stmt {nullptr};
	const int code {::sqlite3_prepare_v2(db.get(), sqlCmd.c_str(), -1,
	                                     &sqlite_stmt, 0)};

	statement stmt {sqlite_stmt};
	if (code != SQLITE_OK) {

		throw sqlite_exeption {code, ::sqlite3_errmsg(db.get()), "sqlite3_prepare"};

	}

	return stmt;
}

int adapter::step(const handle& db, const statement& statement)
{
	const int code {::sqlite3_step(statement.get())};

	if (code != SQLITE_ROW and code != SQLITE_DONE) {

		throw sqlite_exeption {code, ::sqlite3_errmsg(db.get()), "sqlite3_step"};
	}

	return code;
}


using md::model::dal::sqlite::adapter::connector;

connector::connector(handle& db, const std::string& sql_cmd)
	: m_db {db}
	, m_stmt {adapter::prepare_sqlite(db, sql_cmd)}
{ ;}

void connector::bind(const int index, const std::int64_t value)
{
	const int code {::sqlite3_bind_int64(m_stmt.get(), index, value)};

	if (code != SQLITE_OK) {

		throw sqlite_exeption {code, ::sqlite3_errmsg(m_db.get()),
			                       "connector.bind(int64_t)"};
	}
}

void connector::bind(const int index, const QString& value, sqlite3_destructor_type destructor)
{
	QByteArray ba {std::move(value.toLatin1())};

	const int code {::sqlite3_bind_text(m_stmt.get(), index, ba.data(), -1,
	                                    destructor)};

	if (code != SQLITE_OK) {

		throw sqlite_exeption {code, ::sqlite3_errmsg(m_db.get()),
			                       "connecor.bind(QString)"};
	}
}

int connector::step()
{
	const int code {adapter::step(m_db, m_stmt)};

	if (code == SQLITE_DONE) {
		::sqlite3_reset(m_stmt.get());
	}

	return code;
}

std::int64_t connector::read_int64t(const int index)
{
	auto limit {::sqlite3_column_count(m_stmt.get())};

	if (index < 0 or index > limit) {
		throw sqlite_exeption {SQLITE_RANGE, "read index out of range",
			                       "connector.read_int64_t()"};
	}
	return ::sqlite3_column_int64(m_stmt.get(), index);
}

QString connector::read_string(const int index)
{
	auto limit {::sqlite3_column_count(m_stmt.get())};

	if (index < 0 or index > limit) {
		throw sqlite_exeption {SQLITE_RANGE, "read index out of range",
			                       "connector.read_string()"};
	}

	return detail::convert_to_qstring(::sqlite3_column_text(m_stmt.get(), index));
}
