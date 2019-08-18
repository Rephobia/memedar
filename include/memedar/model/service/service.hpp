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


#ifndef MEMEDAR_MODEL_SERVICE_HPP
#define MEMEDAR_MODEL_SERVICE_HPP


#include "memedar/model/service/deck_to_taskbook.hpp"

#include "memedar/model/service/save_unit.hpp"
#include "memedar/model/service/delete_unit.hpp"
#include "memedar/model/service/update_unit.hpp"
#include "memedar/model/service/lesson_unit.hpp"


namespace md::model::dal {
	class mapper;
}

namespace md::model {
	class service;
}


class md::model::service : public virtual md::model::deck_to_taskbook
                         , public md::model::save_unit
                         , public md::model::delete_unit
                         , public md::model::update_unit
                         , public md::model::lesson_unit
{
public:
	explicit service(md::model::dal::mapper& mapper);
protected:
	md::model::dal::mapper& m_mapper;
};


#endif // MEMEDAR_MODEL_SERVICE_HPP
