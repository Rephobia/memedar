#include <ctime>
#include <memory>

#include <QString>

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/card/visitor.hpp"
#include "memedar/model/card/type.hpp"

using md::model::card::card;

card::card(side::side&& question_side,
           side::side&& answer_side,
           bool typing)
	: identity       {identity {}}
	, card::schedule {card::schedule {}}
	, question       {std::move(question_side)}
	, answer         {std::move(answer_side)}
	, m_typing       {typing}
	, m_type         {nullptr}
{ ;}

card::card(identity id,
           card::schedule schedule,
           side::side&& question_side,
           side::side&& answer_side,
           bool typing)
	: identity       {id}
	, card::schedule {schedule}
	, question       {std::move(question_side)}
	, answer         {std::move(answer_side)}
	, m_typing       {typing}
	, m_type         {nullptr}
{ ;}

bool card::has_typing() const
{
	return m_typing;
}

void card::set_type(std::shared_ptr<md::model::card::type> type)
{
	m_type = type;
}

void card::take_visitor(md::model::card::visitor& visitor)
{
	m_type->accept(visitor);
}
