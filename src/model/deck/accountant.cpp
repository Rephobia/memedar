#include <ctime>
#include <memory>

#include <QString>

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/type.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/accountant.hpp"


using md::model::deck::accountant;

accountant::accountant()
	: m_noob       {std::make_shared<card::noob_t>()}
	, m_ready      {std::make_shared<card::ready_t>()}
	, m_delayed    {std::make_shared<card::delayed_t>()}
	, m_noob_db    {0}
	, m_ready_db   {0}
	, m_delayed_db {0}
{ ;}

accountant::accountant(std::int64_t noob_count, std::int64_t ready_count,
                       std::int64_t delayed_count)
	: m_noob       {std::make_shared<card::noob_t>()}
	, m_ready      {std::make_shared<card::ready_t>()}
	, m_delayed    {std::make_shared<card::delayed_t>()}
	, m_noob_db    {noob_count}
	, m_ready_db   {ready_count}
	, m_delayed_db {delayed_count}
{ ;}

accountant::accountant(accountant&& other)
	: m_noob       {std::move(other.m_noob)}
	, m_ready      {std::move(other.m_ready)}
	, m_delayed    {std::move(other.m_delayed)}
	, m_noob_db    {other.m_noob_db}
	, m_ready_db   {other.m_ready_db}
	, m_delayed_db {other.m_delayed_db}
{ ;}

accountant& accountant::operator=(accountant&& other)
{
	if (this != &other) {
		m_noob = std::move(other.m_noob);
		m_ready = std::move(other.m_ready);
		m_delayed = std::move(other.m_delayed);
		m_noob_db = other.m_noob_db;
		m_ready_db = other.m_ready_db;
		m_delayed_db = other.m_delayed_db;
	}

	return *this;
}

void accountant::process_card(card::card& card)
{
	if (card.repeat() == 0) {
		card.set_type(m_noob);
	}
	else if (card.repeat() < std::time(nullptr)) {
		card.set_type(m_ready);
	}
	else {
		card.set_type(m_delayed);
	}
}

std::int64_t accountant::noob_cards(bool is_deck_loaded) const
{
	return is_deck_loaded ? m_noob.use_count() - 1 : m_noob_db;
}

std::int64_t accountant::ready_cards(bool is_deck_loaded) const
{
	return is_deck_loaded ? m_ready.use_count() - 1 : m_ready_db;
}

std::int64_t accountant::delayed_cards(bool is_deck_loaded) const
{
	return is_deck_loaded ? m_delayed.use_count() - 1 : m_delayed_db;
}

std::int64_t accountant::total_cards(bool is_deck_loaded) const
{
	return is_deck_loaded
		? (m_noob.use_count() - 1) + (m_ready.use_count() - 1) + (m_delayed.use_count() - 1)
		: m_noob_db + m_ready_db + m_delayed_db;
}
