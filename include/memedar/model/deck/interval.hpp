#ifndef MEMEDAR_MODEL_DECK_INTERVAL_HPP
#define MEMEDAR_MODEL_DECK_INTERVAL_HPP


namespace md::model::deck {
	class interval;
	using gap_ratio = unsigned int;
}

namespace md::model::card {
	class combo;
}


class md::model::deck::interval
{
public:
	interval();
	interval(std::time_t good_gap, std::time_t easy_gap,
	         md::model::deck::gap_ratio good_ratio,
	         md::model::deck::gap_ratio easy_ratio);

	std::time_t good_interval(md::model::card::combo combo) const;
	std::time_t easy_interval(md::model::card::combo combo) const;

	std::time_t good_gap() const;
	std::time_t easy_gap() const;

	md::model::deck::gap_ratio good_ratio() const;
	md::model::deck::gap_ratio easy_ratio() const;
protected:
	std::time_t calculate_interval(std::time_t gap,
	                               md::model::deck::gap_ratio ratio,
	                               md::model::card::combo combo) const;
protected:
	std::time_t m_good_gap;
	std::time_t m_easy_gap;
	md::model::deck::gap_ratio m_good_ratio;
	md::model::deck::gap_ratio m_easy_ratio;
};


#endif // MEMEDAR_MODEL_DECK_INTERVAL_HPP
