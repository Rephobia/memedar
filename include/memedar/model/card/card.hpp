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


#ifndef MEMEDAR_MODEL_CARD_CARD_HPP
#define MEMEDAR_MODEL_CARD_CARD_HPP


#include <functional>
#include <memory>

#include "memedar/model/identity.hpp"
#include "memedar/model/card/schedule.hpp"
#include "memedar/model/card/combo.hpp"


namespace md::model::card {
	class type;

	struct noob_t;
	struct ready_t;
	struct delayed_t;
	class card;
}


class md::model::card::card : public md::model::identity
                            , public md::model::card::schedule
                            , public md::model::card::combo
{
public:
	card(md::model::side::side&& question,
	     md::model::side::side&& answer,
	     bool typing);

	card(md::model::identity id,
	     md::model::card::schedule schedule,
	     md::model::card::combo combo,
	     md::model::side::side&& question,
	     md::model::side::side&& answer,
	     bool typing);

	md::model::side::side question;
	md::model::side::side answer;

	bool has_typing() const;

	void set_type(std::shared_ptr<md::model::card::type> type);

	void visit(std::function<void(md::model::card::noob_t&)>&& noob,
	           std::function<void(md::model::card::ready_t&)>&& ready,
	           std::function<void(md::model::card::delayed_t&)>&& delayed
	           = [](md::model::card::delayed_t&){});
protected:
	bool m_typing;
	std::shared_ptr<md::model::card::type> m_type;
};


#endif // MEMEDAR_MODEL_CARD_CARD_HPP
