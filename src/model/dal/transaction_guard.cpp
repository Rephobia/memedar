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


#include <iostream>

#include "memedar/model/dal/transaction.hpp"
#include "memedar/model/dal/transaction_guard.hpp"


using md::model::dal::transaction;
using md::model::dal::transaction_guard;

static int active_transaction {0};

transaction_guard md::model::dal::make_transaction(transaction& transaction)
{
	return transaction_guard {transaction};
}

transaction_guard::transaction_guard(transaction& transaction)
	: m_commited    {false}
	, m_transaction {transaction}
{
	if (not active_transaction) {
		m_transaction.begin();
	}
	active_transaction++;
}

void transaction_guard::commit()
{
	if (not --active_transaction) {
		m_transaction.commit();
	}
	m_commited = true;
}

transaction_guard::~transaction_guard()
{
	try {
		if (not m_commited) {
			m_transaction.rollback();
			active_transaction = 0;
		}
	}
	catch (std::runtime_error &e) {

		std::cout << e.what() << std::endl;
	}
}
