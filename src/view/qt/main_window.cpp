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


#include <QMainWindow>
#include <QScrollArea>

#include "memedar/view/qt/main_window.hpp"


using md::view::qt::main_window;

main_window::main_window()
	: m_main_area {new QScrollArea {}}
{
	m_main_area->setWidgetResizable(true);
}

void main_window::set_widget(QWidget* new_widget)
{
	auto old_widget = m_main_area->takeWidget();

	m_main_area->setWidget(new_widget);

	if (old_widget) {
		old_widget->deleteLater();
	}
	else {
		this->setCentralWidget(m_main_area);
	}
}
