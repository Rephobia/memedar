#include <ctime>
#include <algorithm>

#include "memedar/model/card/schedule.hpp"


using md::model::card::combo;

combo::combo(int value)
	: m_value {std::clamp(value, MIN_COMBO, MAX_COMBO)}
{ ;}

combo::operator int() const
{
	return m_value;
}

combo& combo::operator++()
{
	++m_value;
	return *this;
}

int operator*(const int lhs, const combo rhs)
{
	return lhs * rhs.m_value;
}

int operator*(const combo lhs, const int rhs)
{
	return lhs.m_value * rhs;
}


using md::model::card::schedule;

schedule::schedule()
	: m_added  {std::time(nullptr)}
	, m_repeat {0}
	, m_combo  {card::combo {}}
{ ;}

schedule::schedule(std::time_t added, std::time_t repeat, card::combo combo)
	: m_added  {added}
	, m_repeat {repeat}
	, m_combo  {combo}
{ ;}

std::time_t schedule::added() const
{
	return m_added;
}

std::time_t schedule::repeat() const
{
	return m_repeat;
}

void schedule::change_repeat(std::time_t val)
{
	m_repeat = val;
}

combo schedule::combo() const
{
	return m_combo;
}

void schedule::increment_combo()
{
	++m_combo;
}

void schedule::reset_combo()
{
	m_combo = card::combo {};
}
