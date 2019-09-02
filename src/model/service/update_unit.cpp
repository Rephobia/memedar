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


#include <deque>


#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/taskbook.hpp"

#include "memedar/model/dal/transaction_guard.hpp"
#include "memedar/model/dal/mapper.hpp"

#include "memedar/model/service/update_unit.hpp"


using md::model::update_unit;

update_unit::update_unit(dal::mapper& mapper)
	: deck_to_taskbook {mapper}
	, m_mapper         {mapper}
{ ;}

bool update_unit::update_card(deck::deck& deck,
                              card::card& card, card::card_dto&& new_card)
{
	decltype(auto) transaction {m_mapper.make_transaction()};

	bool updated = false;
	
	if (card.question.text() != new_card.question.text()) {
		update_side(card.question, std::move(new_card.question));
		updated = true;
	}
	
	if (card.answer.text() != new_card.answer.text()) {
		update_side(card.answer, std::move(new_card.answer));
		updated = true;
	}

	if (card.has_typing != new_card.value.has_typing) {
		m_mapper.card->update_card(card, new_card.value.has_typing);
		card.has_typing = new_card.value.has_typing;
		updated = true;
	}

	if (updated) {
		if (std::optional<task::task*> task_opt {get_task(deck, card)}) {
			update_task(*(task_opt.value()));
		}
	}
	
	transaction.commit();
	
	return updated;
}

void update_unit::update_side(side::side& old_side, side::side_value&& new_side)
{
	m_mapper.card->update_side(old_side, new_side);
	old_side = std::move(new_side);	
}

void update_unit::update_task(task::task& task)
{
	m_mapper.card->reset_combo(*task.card);
	m_mapper.task->change_state(task, task::state::answering);
}

void update_unit::update_deck(md::model::deck::deck& deck,
                              md::model::deck::deck_value&& new_deck)
{
	decltype(auto) transaction {m_mapper.make_transaction()};
	
	if (deck.name() != new_deck.name()) {
		m_mapper.deck->update_deck(deck, new_deck);
		deck.change_name(std::move(new_deck.name()));
	}
	
	transaction.commit();
}
