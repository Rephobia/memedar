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


#ifndef MEMEDAR_MODEL_TASK_ADD_VISITOR_HPP
#define MEMEDAR_MODEL_TASK_ADD_VISITOR_HPP


namespace md::model::task {
	class add_visitor;
}

class md::model::task::add_visitor : public md::model::card::visitor
{
public:
	add_visitor(md::model::task::task_book& task_book,
	            md::model::task::task task);

	void visit(md::model::card::noob_t& ref) override;
	void visit(md::model::card::ready_t& ref) override;
	void visit(md::model::card::delayed_t& ref) override;

	bool is_task() const;
protected:
	md::model::task::task_book& m_task_book;
	md::model::task::task m_task;
	bool m_task_status;
};


#endif // MEMEDAR_MODEL_TASK_ADD_VISITOR_HPP
