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


#include <ctime>
#include <memory>
#include <deque>


#include <sqlite3.h>
#include <QString>


#include "memedar/model/dal/transaction.hpp"
#include "memedar/model/dal/card_mapper.hpp"
#include "memedar/model/dal/deck_mapper.hpp"
#include "memedar/model/dal/task_mapper.hpp"
#include "memedar/model/dal/transaction_guard.hpp"

#include "memedar/model/dal/sqlite/adapter.hpp"
#include "memedar/model/dal/sqlite/transaction.hpp"
#include "memedar/model/dal/sqlite/card_mapper.hpp"
#include "memedar/model/dal/sqlite/deck_mapper.hpp"
#include "memedar/model/dal/sqlite/task_mapper.hpp"
#include "memedar/model/dal/mapper.hpp"


using md::model::dal::mapper;

md::model::dal::mapper md::model::dal::make_sqlite(const std::filesystem::path& path)
{
	static auto db {md::model::dal::sqlite::adapter::open_sqlite(path)};

	return mapper { std::make_unique<md::model::dal::sqlite::card_mapper>(db),
			std::make_unique<md::model::dal::sqlite::deck_mapper>(db),
			std::make_unique<md::model::dal::sqlite::task_mapper>(db),
			std::make_unique<md::model::dal::sqlite::transaction>(db) };
}

mapper::mapper(std::unique_ptr<md::model::dal::card_mapper> card_mapper,
	       std::unique_ptr<md::model::dal::deck_mapper> deck_mapper,
	       std::unique_ptr<md::model::dal::task_mapper> task_mapper,
	       std::unique_ptr<md::model::dal::transaction> transaction_mapper)
	: card        {std::move(card_mapper)}
	, deck        {std::move(deck_mapper)}
	, task        {std::move(task_mapper)}
	, transaction {std::move(transaction_mapper)}
{
	auto guard {make_transaction()};
		
	card->create_table();
	deck->create_table();
	task->create_table();

	guard.commit();
}

md::model::dal::transaction_guard mapper::make_transaction()
{
	return dal::make_transaction(*transaction);
}
