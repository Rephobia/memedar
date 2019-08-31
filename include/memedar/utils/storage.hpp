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


#ifndef MEMEDAR_UTILS_STORAGE_HPP
#define MEMEDAR_UTILS_STORAGE_HPP


#include <vector>

namespace md::utils {
	template<class T>
	class storage;

	template<class T>
	class storage_with_add;
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
		: m_container {std::move(other.m_container)}
	{ ;}

	storage& operator=(storage&& other)
	{
		if (this != &other) {
			m_container = std::move(other.m_container);
		}
		return *this;
	}

	T& index(typename container::size_type pos)
	{
		return m_container[pos];
	}
		
	const T& index(typename container::size_type pos) const
	{
		return m_container[pos];
	}
	
	iterator begin()
	{
		return m_container.begin();
	}

	iterator end()
	{
		return m_container.end();
	}

	const_iterator begin() const
	{
		return m_container.begin();
	}

	const_iterator end() const
	{
		return m_container.end();
	}

	typename container::size_type size() const
	{
		return m_container.size();
	}

	bool empty() const
	{
		return m_container.empty();
	}
protected:
	void add(const T& value)
	{
		m_container.push_back(value);
	}
	
	void add(T&& value)
	{
		m_container.push_back(std::forward<T>(value));
	}
private:
	container m_container {};
};


template<class T>
class md::utils::storage_with_add : public md::utils::storage<T>
{
public:
	storage_with_add() = default;
	
	void add(const T& value)
	{
		storage<T>::add(value);
	}
	
	void add(T&& value)
	{
		storage<T>::add(std::forward<T>(value));
	}
};


#endif // MEMEDAR_UTILS_STORAGE_HPP
