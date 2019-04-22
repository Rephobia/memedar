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


#ifndef MEMEDAR_VIEW_QT_UI_BUTTON_HPP
#define MEMEDAR_VIEW_QT_UI_BUTTON_HPP

#include <QPushButton>

namespace md::view::qt::ui {
	class button;
}


class md::view::qt::ui::button : public QPushButton
{
public:
	template<class... A>
	button(QString text, A... actions)
	{
		this->setText(text);
		this->attach(actions...);
	}
	template<class... A>
	void attach(A... actions)
	{
		[[maybe_unused]] auto unused =
			{true, ((void) this->tie(actions), true)...};
	}

protected:
	template<class Lambda>
	void tie(Lambda lambda)
	{
		QObject::connect(this, &QPushButton::clicked, lambda);
	}
	void tie(const QKeySequence& shortcut)
	{
		this->setShortcut(shortcut);
	}
};


#endif // MEMEDAR_VIEW_QT_UI_BUTTON_HPP
