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


#ifndef MEMEDAR_UTILS_STORAGE_HPP
#define MEMEDAR_UTILS_STORAGE_HPP


#include <vector>

namespace md::utils {
	template<class T>
	class storage;
}


template<class T>
class md::utils::storage
{
public:
	using container = std::vector<T>;
	using iterator = typename container::iterator;
	using const_iterator = typename container::const_iterator;
	using value_type = typename container::value_type;
	
	storage() = default;

	storage(const storage& other) = delete;
	storage operator=(const storage& other) = delete;

	storage(storage&& other)
		: m_storage {std::move(other.m_storage)}
	{ ;}

	storage& operator=(storage&& other)
	{
		if (this != &other) {
			m_storage = std::move(other.m_storage);
		}
		return *this;
	}

	T& index(typename container::size_type pos)
	{
		return m_storage[pos];
	}
		
	const T& index(typename container::size_type pos) const
	{
		return m_storage[pos];
	}
	
	iterator begin()
	{
		return m_storage.begin();
	}

	iterator end()
	{
		return m_storage.end();
	}

	const_iterator begin() const
	{
		return m_storage.begin();
	}

	const_iterator end() const
	{
		return m_storage.end();
	}

	T& back()
	{
		return m_storage.back();
	}

	const T& back() const
	{
		return m_storage.back();
	}

	typename container::size_type size() const
	{
		return m_storage.size();
	}

	bool empty() const
	{
		return m_storage.empty();
	}

	void add(T&& value)
	{
		m_storage.push_back(std::forward<T>(value));
	}
private:
	container m_storage {container {}};
};


#endif // MEMEDAR_UTILS_STORAGE_HPP
