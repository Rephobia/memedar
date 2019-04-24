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


#ifndef MEMEDAR_MODEL_DAL_TRANSACTION_GUARD_HPP
#define MEMEDAR_MODEL_DAL_TRANSACTION_GUARD_HPP


namespace md::model::dal {
	class transaction;
	class transaction_guard;
	transaction_guard make_transaction(transaction& transaction);
}


class md::model::dal::transaction_guard
{
public:
	explicit transaction_guard(md::model::dal::transaction& transaction);

	void commit();

	~transaction_guard();
protected:
	bool m_commited;
	md::model::dal::transaction& m_transaction;
};


#endif // MEMEDAR_MODEL_DAL_TRANSACTION_GUARD_HPP
