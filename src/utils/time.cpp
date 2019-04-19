#include <ctime>

#include "memedar/utils/time.hpp"


bool md::utils::time::is_today(std::time_t timestamp)
{
	std::time_t current_day {std::time(nullptr) / DAY};

	return (timestamp / DAY) == current_day;
}
