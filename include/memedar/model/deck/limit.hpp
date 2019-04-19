#ifndef MEMEDAR_MODEL_DECK_LIMIT_HPP
#define MEMEDAR_MODEL_DECK_LIMIT_HPP


namespace md::model::deck {
	class limit;
}


class md::model::deck::limit
{
public:
	limit() = default;
	limit(std::int64_t max_noob, std::int64_t max_ready,
	      std::int64_t daily_noob, std::int64_t daily_ready);

	std::int64_t max_noob_cards() const;
	std::int64_t max_ready_cards() const;
	std::int64_t daily_noob_cards() const;
	std::int64_t daily_ready_cards() const;

	void decrement_daily_noob();
	void decrement_daily_ready();
	void reset_daily();
private:
	enum : int { DEFAULT_MAX = 100000 };

	std::int64_t m_max_noob = DEFAULT_MAX;
	std::int64_t m_max_ready = DEFAULT_MAX;
	std::int64_t m_daily_noob = DEFAULT_MAX;
	std::int64_t m_daily_ready = DEFAULT_MAX;
};


#endif // MEMEDAR_MODEL_DECK_LIMIT_HPP
