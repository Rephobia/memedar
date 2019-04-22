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


#ifndef MEMEDAR_UTILS_FIND_HPP
#define MEMEDAR_UTILS_FIND_HPP


namespace md::utils {
	template<class T>
	class storage;
}

namespace md::utils {

	template<class T>
	typename utils::storage<T>::iterator
	find_by_id(std::int64_t id, utils::storage<T>& storage)
	{
		auto find {[id, &storage](const T& obj)
		           { return obj.id() == id; }};

		return std::find_if(storage.begin(), storage.end(), find);
	}
	template<class T>
	typename utils::storage<std::unique_ptr<T>>::iterator
	find_by_id(std::int64_t id, utils::storage<std::unique_ptr<T>>& storage)
	{
		auto find {[id, &storage](const std::unique_ptr<T>& obj)
		           { return obj->id() == id; }};

		return std::find_if(storage.begin(), storage.end(), find);
	}
}


#endif // MEMEDAR_UTILS_FIND_HPP
