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


#ifndef MEMEDAR_MODEL_TASK_TASK_HPP
#define MEMEDAR_MODEL_TASK_TASK_HPP


#include "memedar/model/identity.hpp"

namespace md::model::task {
	class task;
	enum class state : int { answering = 0, marking, done };

}


class md::model::task::task : public md::model::identity
{
public:
	task(std::shared_ptr<md::model::card::card> card,
	     md::model::task::state state);

	std::shared_ptr<md::model::card::card> card;
	md::model::task::state state;
	QString user_answer;
};


#endif // MEMEDAR_MODEL_TASK_TASK_HPP
