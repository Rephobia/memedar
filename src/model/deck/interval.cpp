#include <ctime>

#include "memedar/utils/time.hpp"
#include "memedar/utils/constants.hpp"
#include "memedar/model/card/schedule.hpp"
#include "memedar/model/deck/interval.hpp"


using md::model::deck::gap_ratio;
using md::model::deck::interval;

interval::interval()
	: m_good_gap   {utils::time::DAY}
	, m_easy_gap   {utils::time::DAY * 3}
	, m_good_ratio {utils::constants::PTC_100}
	, m_easy_ratio {utils::constants::PTC_200}
{ ;}

interval::interval(std::time_t good_gap, std::time_t easy_gap,
                   gap_ratio good_ratio,
                   gap_ratio easy_ratio)
	: m_good_gap   {good_gap}
	, m_easy_gap   {easy_gap}
	, m_good_ratio {good_ratio}
	, m_easy_ratio {easy_ratio}
{ ;}

std::time_t interval::good_interval(card::combo combo) const
{
	return calculate_interval(m_good_gap, m_good_ratio, combo);
}

std::time_t  interval::easy_interval(card::combo combo) const
{
	return calculate_interval(m_easy_gap, m_easy_ratio, combo);
}

std::time_t interval::calculate_interval(std::time_t gap,
                                         gap_ratio ratio,
                                         card::combo combo) const
{
	return gap/utils::constants::PTC_100 * ratio * combo
		+ gap
		- gap/utils::constants::PTC_100 * ratio;
}

std::time_t interval::good_gap() const
{
	return m_good_gap;
}

std::time_t interval::easy_gap() const
{
	return m_easy_gap;
}

gap_ratio interval::good_ratio() const
{
	return m_good_ratio;
}

gap_ratio interval::easy_ratio() const
{
	return m_easy_ratio;
}
