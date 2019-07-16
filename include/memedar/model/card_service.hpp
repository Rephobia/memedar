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


#ifndef MEMEDAR_MODEL_CARD_SERVICE_HPP
#define MEMEDAR_MODEL_CARD_SERVICE_HPP


namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
}

namespace md::model::dal {
	class mapper;
}

namespace md::model {
	class card_service;
}


class md::model::card_service
{
public:
	explicit card_service(md::model::dal::mapper& mapper);

	void save_card(md::model::deck::deck& deck, md::model::card::card&& card);
protected:
	md::model::dal::mapper& m_mapper;
};


#endif // MEMEDAR_MODEL_CARD_SERVICE_HPP
