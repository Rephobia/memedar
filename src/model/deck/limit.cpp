#include <cstdint>

#include "memedar/model/deck/limit.hpp"

using md::model::deck::limit;

limit::limit(std::int64_t max_noob, std::int64_t max_ready,
             std::int64_t daily_noob, std::int64_t daily_ready)
	: m_max_noob    {max_noob}
	, m_max_ready   {max_ready}
	, m_daily_noob  {daily_noob}
	, m_daily_ready {daily_ready}
{ ;}

std::int64_t limit::max_noob_cards() const
{
	return m_max_noob;
}

std::int64_t limit::max_ready_cards() const
{
	return m_max_ready;
}

std::int64_t limit::daily_noob_cards() const
{
	return m_daily_noob;
}

std::int64_t limit::daily_ready_cards() const
{
	return m_daily_ready;
}

void limit::decrement_daily_noob()
{
	--m_daily_noob;
}

void limit::decrement_daily_ready()
{
	--m_daily_ready;
}

void limit::reset_daily()
{
	m_daily_noob = m_max_noob;
	m_daily_ready = m_max_ready;
}
