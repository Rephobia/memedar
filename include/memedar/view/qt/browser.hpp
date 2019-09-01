/*
 * SPDX-License-Identifier: GPL-3.0-or-later

 * Copyright (C) 2019 Roman Erdyakov

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


#ifndef MEMEDAR_VIEW_QT_BROWSER_HPP
#define MEMEDAR_VIEW_QT_BROWSER_HPP


#include <QTableView>


class QWidget;
class QStandardItemModel;


namespace md::view::qt {
	class browser;
}


#pragma GCC diagnostic ignored "-Weffc++"

class md::view::qt::browser : public md::view::browser
{
public:
	class table_row;
	class table;
	
	explicit browser(md::view::qt::main_window* main_window);
	
	void show(std::deque<md::model::deck::deck>& decks) override;
protected:
	md::view::qt::main_window* m_main_window;	
};


class md::view::qt::browser::table_row
{
public:
	table_row(md::model::deck::deck& new_deck,
	          md::model::card::card& new_card);

	md::model::deck::deck& deck;
	md::model::card::card& card;	
};


class md::view::qt::browser::table : public QTableView
{
public:
	explicit table(QWidget* parent);
	void add_row(md::model::deck::deck& deck, md::model::card::card& card);
	md::model::card::card& get_card(std::size_t row_index);
protected:
	QStandardItemModel* m_model;
	enum column : int {deck = 0, question, answer};
	std::size_t m_row {0};
protected:
	std::vector<md::view::qt::browser::table_row> m_rows {};
};

#pragma GCC diagnostic pop


#endif // MEMEDAR_VIEW_QT_BROWSER_HPP
