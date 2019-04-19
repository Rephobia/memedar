#include <ctime>
#include <memory>

#include <QString>

#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"

using md::model::deck::deck;

deck::deck(deck::info&& info)
	: deck::identity {identity {}}
	, deck::info     {std::move(info)}
	, deck::limit    {limit {}}
	, deck::interval {interval {}}
	, m_accountant   {md::model::deck::accountant {}}
{ ;}

deck::deck(deck::identity id,
           deck::info&& info,
           deck::limit limit,
           deck::interval interval,
           md::model::deck::accountant&& accountant)
	: deck::identity {id}
	, deck::info     {std::move(info)}
	, deck::limit    {limit}
	, deck::interval {interval}
	, m_accountant   {std::move(accountant)}
{ ;}

void deck::process_card(card::card& card)
{
	m_accountant.process_card(card);
}

void deck::add_card(card::card&& card)
{
	m_accountant.process_card(card);
	storage::add(std::move(card));
}

std::int64_t deck::noob_cards() const
{
	return m_accountant.noob_cards(not storage::empty());
}

std::int64_t deck::ready_cards() const
{
	return m_accountant.ready_cards(not storage::empty());
}

std::int64_t deck::delayed_cards() const
{
	return m_accountant.delayed_cards(not storage::empty());
}

std::int64_t deck::total_cards() const
{
	return m_accountant.total_cards(not storage::empty());
}
