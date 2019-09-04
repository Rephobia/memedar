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


#ifndef MEMEDAR_MODEL_CARD_VISITOR_HPP
#define MEMEDAR_MODEL_CARD_VISITOR_HPP


namespace md::model::card {
	struct visitor;

	struct noob_t;
	struct ready_t;
	struct delayed_t;
}


struct md::model::card::visitor
{
	visitor(std::function<void(md::model::card::noob_t&)>&& noob,
	        std::function<void(md::model::card::ready_t&)>&& ready,
	        std::function<void(md::model::card::delayed_t&)>&& delayed);
	void visit(md::model::card::noob_t&);
	void visit(md::model::card::ready_t&);
	void visit(md::model::card::delayed_t&);
protected:
	std::function<void(md::model::card::noob_t&)> m_noob;
	std::function<void(md::model::card::ready_t&)> m_ready;
	std::function<void(md::model::card::delayed_t&)> m_delayed;
};


#endif // MEMEDAR_MODEL_CARD_VISITOR_HPP
