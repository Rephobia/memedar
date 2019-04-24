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


#ifndef MEMEDAR_MODEL_DAL_SQLITE_TRANSACTION_HPP
#define MEMEDAR_MODEL_DAL_SQLITE_TRANSACTION_HPP


namespace md::model::dal::sqlite {
	namespace transaction_resources {
		std::string begin_cmd();
		std::string commit_cmd();
		std::string rollback_cmd();
	}
	class transaction;
}


class md::model::dal::sqlite::transaction : public md::model::dal::transaction
{
public:
	explicit transaction(md::model::dal::sqlite::adapter::handle& db);
	void begin() override;
	void commit() override;
	void rollback() override;
protected:
	md::model::dal::sqlite::adapter::handle& m_db;
};


#endif // MEMEDAR_MODEL_DAL_SQLITE_TRANSACTION_HPP
