 /*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov

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


#ifndef MEMEDAR_MODEL_DAL_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_MAPPER_HPP


#include <filesystem>

#include "memedar/model/dal/card_mapper.hpp"
#include "memedar/model/dal/deck_mapper.hpp"
#include "memedar/model/dal/task_mapper.hpp"
#include "memedar/model/dal/transaction.hpp"

namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
	class deck_value;
}

namespace md::model::dal {
	class mapper;
	md::model::dal::mapper make_sqlite(const std::filesystem::path& path);
	class transaction_guard;
}

namespace md::model::task {
	class task;
	class taskbook;
}


class md::model::dal::mapper
{
public:
	mapper(std::unique_ptr<md::model::dal::card_mapper> card_mapper,
	       std::unique_ptr<md::model::dal::deck_mapper> deck_mapper,
	       std::unique_ptr<md::model::dal::task_mapper> task_mapper,
	       std::unique_ptr<md::model::dal::transaction> transaction_mapper);

	std::unique_ptr<md::model::dal::card_mapper> card;
	std::unique_ptr<md::model::dal::deck_mapper> deck;
	std::unique_ptr<md::model::dal::task_mapper> task;
	
	md::model::dal::transaction_guard make_transaction();
	
protected:
	std::unique_ptr<md::model::dal::transaction> transaction;
};


#endif // MEMEDAR_MODEL_DAL_MAPPER_HPP
