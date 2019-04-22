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


#ifndef MEMEDAR_MENU_PRESENTER_HPP
#define MEMEDAR_MENU_PRESENTER_HPP


namespace md::view {
	class menu;
}

namespace md {
	class menu_presenter;
}


class md::menu_presenter
{
public:
	explicit menu_presenter(md::view::menu& menu);
	boost::signals2::signal<void()> go_to_designer {};
protected:
	md::view::menu& m_menu;
};


#endif // MEMEDAR_MENU_PRESENTER_HPP
