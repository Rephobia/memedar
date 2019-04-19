#ifndef MEMEDAR_MODEL_TASK_TASK_BOOK_HPP
#define MEMEDAR_MODEL_TASK_TASK_BOOK_HPP


namespace md::utils {
	template<class T>
	class storage;
}

namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
}

namespace md::model::task {
	enum class state : int;
	class task;

	class add_visitor;
	class task_book;
}


class md::model::task::task_book : public md::utils::storage<md::model::task::task>
{
public:
	explicit task_book(md::model::deck::deck& deck);
	bool add_card(md::model::card::card& card);
	void add_card(md::model::card::card& card, md::model::task::state state);

	std::int64_t noob_space() const;
	std::int64_t ready_space() const;
	std::int64_t space() const;

	md::model::deck::deck& deck;
private:
	friend class md::model::task::add_visitor;
	using storage::add;
protected:
	std::int64_t m_noob_space;
	std::int64_t m_ready_space;
};



#endif // MEMEDAR_MODEL_TASK_TASK_BOOK_HPP
