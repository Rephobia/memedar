#ifndef MEMEDAR_UTILS_TIME_HPP
#define MEMEDAR_UTILS_TIME_HPP


namespace md::utils::time {

	inline constexpr std::time_t MINUTE {60};
	inline constexpr std::time_t DAY {86400};

	bool is_today(std::time_t timestamp);
}


#endif // MEMEDAR_UTILS_TIME_HPP
