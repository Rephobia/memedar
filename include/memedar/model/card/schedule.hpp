#ifndef MEMEDAR_MODEL_CARD_SCHEDULE_HPP
#define MEMEDAR_MODEL_CARD_SCHEDULE_HPP


namespace md::model::card {
	class combo;
	class schedule;
}

int operator*(const int lhs, const md::model::card::combo rhs);
int operator*(const md::model::card::combo lhs, const int rhs);

class md::model::card::combo
{
private:
	static constexpr int MIN_COMBO {1};
	static constexpr int MAX_COMBO {600};
public:
	explicit combo(int value = MIN_COMBO);

	explicit operator int() const;

	md::model::card::combo& operator++();
	friend int ::operator*(const int lhs, const md::model::card::combo rhs);
	friend int ::operator*(const md::model::card::combo lhs, const int rhs);
private:
	int m_value;
};


class md::model::card::schedule
{
public:
	schedule();
	schedule(std::time_t added, std::time_t repeat,
	         md::model::card::combo combo);

	std::time_t added() const;

	std::time_t repeat() const;
	void change_repeat(std::time_t val);

	md::model::card::combo combo() const;
	void increment_combo();
	void reset_combo();

protected:
	std::time_t m_added;
	std::time_t m_repeat;
	md::model::card::combo m_combo;
};


#endif // MEMEDAR_MODEL_CARD_SCHEDULE_HPP
