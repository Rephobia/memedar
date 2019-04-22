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


#ifndef MEMEDAR_VIEW_QT_UI_BOX_HPP
#define MEMEDAR_VIEW_QT_UI_BOX_HPP


#include <QBoxLayout>

namespace md::view::qt::ui {
	class box;
}


#pragma GCC diagnostic ignored "-Weffc++"

class md::view::qt::ui::box : public QWidget
{
public:
	template<class... W>
	box(QBoxLayout::Direction dir, W... widgets)
		: m_layout {new QBoxLayout {dir, this}}
	{
		this->put_widget(widgets...);
	}
	template<class... W>
	void put_widget(W... widgets)
	{
		[[maybe_unused]] auto unused =
			{true, ((void) m_layout->addWidget(widgets), true)... };
	}
	template<class... W>
	void set_widget(W... widgets)
	{
		while (auto w = findChild<QWidget*>()) {
			delete w;
		}
		this->put_widget(widgets...);
	}
	template<class... W>
	void put_widget(QBoxLayout::Direction dir, W... widgets)
	{
		this->put_widget(new md::view::qt::ui::box {dir, widgets...});
	}
	template<class... W>
	void set_widget(QBoxLayout::Direction dir, W... widgets)
	{
		while (auto w = findChild<QWidget*>()) {
			delete w;
		}
		this->put_widget(dir, widgets...);
	}
protected:
	QBoxLayout* m_layout;
};

#pragma GCC diagnostic pop


#endif // MEMEDAR_VIEW_QT_UI_BOX_HPP
