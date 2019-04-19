#include <ctime>
#include <memory>

#include <QString>

#include "memedar/utils/find.hpp"
#include "memedar/utils/storage.hpp"
#include "memedar/utils/ref_wrapper.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"
#include "memedar/model/task/task.hpp"
#include "memedar/model/task/task_book.hpp"
#include "memedar/model/card/visitor.hpp"
#include "memedar/model/task/add_visitor.hpp"


using md::model::task::task_book;

task_book::task_book(deck::deck& deck)
	: deck          {deck}
	, m_noob_space  {deck.daily_noob_cards()}
	, m_ready_space {deck.daily_ready_cards()}
{ ;}

bool task_book::add_card(card::card& card)
{
	add_visitor visitor {*this, card, state::answering};

	if (utils::find_by_id(card.id(), *this) == storage::end()) {
		card.take_visitor(visitor);
	}
	return visitor.is_task();
}

void task_book::add_card(card::card& card, md::model::task::state state)
{
	add_visitor visitor {*this, card, state};

	card.take_visitor(visitor);
}

std::int64_t task_book::noob_space() const
{
	return m_noob_space;
}

std::int64_t task_book::ready_space() const
{
	return m_ready_space;
}

std::int64_t task_book::space() const
{
	return noob_space() + ready_space();
}
