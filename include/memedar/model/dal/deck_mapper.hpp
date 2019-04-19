#ifndef MEMEDAR_MODEL_DAL_DECK_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_DECK_MAPPER_HPP


namespace md::model::deck {
	class deck;
}

namespace md::model::dal {
	class deck_mapper;
}


class md::model::dal::deck_mapper
{
public:
	virtual void create_table() = 0;

	virtual md::utils::storage<md::model::deck::deck> load_decks() = 0;
	virtual void save_deck(md::model::deck::deck& deck) = 0;

	virtual	void decrement_daily_noob(md::model::deck::deck& deck) = 0;
	virtual	void decrement_daily_ready(md::model::deck::deck& deck) = 0;
	virtual void update_last_opening(md::model::deck::deck& deck) = 0;
	virtual void reset_daily(md::model::deck::deck& deck) = 0;

	virtual ~deck_mapper() = default;
};


#endif // MEMEDAR_MODEL_DAL_DECK_MAPPER_HPP
