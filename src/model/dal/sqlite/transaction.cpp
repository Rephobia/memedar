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

#include "memedar/model/dal/transaction.hpp"
#include "memedar/model/dal/sqlite/adapter.hpp"
#include "memedar/model/dal/sqlite/transaction.hpp"

namespace res =  md::model::dal::sqlite::transaction_resources;

std::string res::begin_cmd()
{
	std::string cmd {"begin"};
	return cmd;
}

std::string res::commit_cmd()
{
	std::string cmd {"commit"};
	return cmd;
}

std::string res::rollback_cmd()
{
	std::string cmd {"rollback"};
	return cmd;
}


using md::model::dal::sqlite::transaction;
using md::model::dal::sqlite::adapter::connector;

transaction::transaction(md::model::dal::sqlite::adapter::handle& db)
	: m_db {db}
{ ;}

void transaction::begin()
{
	static connector conn {m_db, res::begin_cmd()};
	conn.step();
}

void transaction::commit()
{
	static connector conn {m_db, res::commit_cmd()};
	conn.step();
}

void transaction::rollback()
{
	static connector conn {m_db, res::rollback_cmd()};
	conn.step();
}
