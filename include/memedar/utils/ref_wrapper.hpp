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


#ifndef MEMEDAR_UTILS_REF_WRAPPER_HPP
#define MEMEDAR_UTILS_REF_WRAPPER_HPP


namespace md::utils {
	template <class T>
	class ref_wrapper;
}


template <class T>
class md::utils::ref_wrapper
{
public:
	explicit ref_wrapper(T& ref)
		:   m_ref {ref}
	{ ;}
	explicit ref_wrapper(const std::reference_wrapper<T>& ref)
		:   m_ref {ref}
	{ ;}

	operator const T& () const noexcept
	{
		return m_ref.get();
	}

	operator T& () noexcept
	{
		return m_ref.get();
	}

	const T& get() const noexcept
	{
		return m_ref.get();
	}

	T& get() noexcept
	{
		return m_ref.get();
	}
protected:
	std::reference_wrapper<T> m_ref;
};


#endif // MEMEDAR_UTILS_REF_WRAPPER_HPP
