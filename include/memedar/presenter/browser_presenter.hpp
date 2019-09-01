/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov (Linhurdos) <teremdev@gmail.com>

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


#ifndef MEMEDAR_BROWSER_PRESENTER_HPP
#define MEMEDAR_BROWSER_PRESENTER_HPP


namespace md::model {
	class service;
}

namespace md::view {
	class browser;
	class error_delegate;
}

namespace md {
	class presenter;
	class browser_presenter;
	class controller;
}


class md::browser_presenter : public md::presenter
{
public:
	browser_presenter(md::controller& controller,
	                  md::model::service& service,
	                  md::view::error_delegate& error_delegate,
	                  md::view::browser& browser);
	
	void run() override;
protected:
	md::controller& m_controller;
	md::model::service& m_service;
	md::view::error_delegate& m_error_delegate;
	md::view::browser& m_browser;
};




#endif // MEMEDAR_BROWSER_PRESENTER_HPP
