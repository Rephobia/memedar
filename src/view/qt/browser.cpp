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


#include <ctime>
#include <memory>
#include <deque>

#include <boost/signals2.hpp>
#include <QString>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>

#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"

#include "memedar/view/browser.hpp"
#include "memedar/view/qt/ui/button.hpp"
#include "memedar/view/qt/ui/box.hpp"
#include "memedar/view/qt/main_window.hpp"
#include "memedar/view/qt/browser.hpp"


using md::view::qt::browser;

browser::table_row::table_row(md::model::deck::deck& new_deck,
                              md::model::card::card& new_card)
	: deck {new_deck}
	, card {new_card}
{ ;}

browser::table::table(QWidget* parent)
	: QTableView {parent}
	, m_model    {new QStandardItemModel {}}
{
	m_model->setHorizontalHeaderLabels({"deck", "question", "answer"});
	
	QTableView::setSelectionBehavior(QAbstractItemView::SelectRows);
	QTableView::setSelectionMode(QAbstractItemView::SingleSelection);
	
	QTableView::setEditTriggers(QAbstractItemView::NoEditTriggers);
	

	QTableView::setModel(m_model);
}


md::view::qt::browser::table_row browser::table::get_row(std::size_t row_index)
{
	return m_rows[row_index];
}

void browser::table::add_row(md::model::deck::deck& deck, md::model::card::card& card)
{
	m_model->setItem(m_row, column::deck, new QStandardItem {deck.name()});
	m_model->setItem(m_row, column::question, new QStandardItem {card.question.text()});
	m_model->setItem(m_row, column::answer, new QStandardItem {card.answer.text()});
	
	m_rows.push_back(table_row {deck, card});
	
	m_row++;
}


browser::browser(qt::main_window* main_window)
	: m_main_window {main_window}
{ ;}

void browser::show(std::deque<md::model::deck::deck>& decks)
{
	auto table {new browser::table {m_main_window}};
	
	for (auto& deck : decks) {
		
		for (auto& card : deck.cards()) {

			table->add_row(deck, *card);

		}
	}
	
	QObject::connect(table,
	                 &QAbstractItemView::doubleClicked,
	                 [this, table](const QModelIndex& index)
	                 {
		                 decltype(auto) row {table->get_row(index.row())};
		                 call_designer(row.deck, row.card);
	                 });
	
	m_main_window->set_widget(table);
}
