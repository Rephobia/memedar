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


#include <QLabel>

#include "memedar/view/error_delegate.hpp"

#include "memedar/view/qt/ui/button.hpp"
#include "memedar/view/qt/ui/box.hpp"
#include "memedar/view/qt/error_delegate.hpp"


using md::view::qt::error_delegate;

error_delegate::error_delegate()
	: box      {QBoxLayout::TopToBottom}
	, m_text   {new QLabel {}}
{
	box::put_widget(m_text, new ui::button {"ok", [this]() { box::hide(); }});
}

void error_delegate::show_error(std::system_error &e)
{
	m_text->setText(e.what());
	box::show();
}

void error_delegate::show_error(QString message)
{
	m_text->setText(std::move(message));
	box::show();
}
