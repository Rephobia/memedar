#ifndef MEMEDAR_MODEL_DAL_CARD_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_CARD_MAPPER_HPP


namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
}

namespace md::model::dal {
	class card_mapper;
}


class md::model::dal::card_mapper
{
public:
	virtual void create_table() = 0;

	virtual	void save_card(md::model::deck::deck& deck,
		               md::model::card::card&& card) = 0;
	virtual void load_cards(md::model::deck::deck& deck) = 0;

	virtual void update_repeat(md::model::card::card& card, std::time_t repeat) = 0;
	virtual void reset_combo(md::model::card::card& card) = 0;

	virtual ~card_mapper() = default;
};


#endif // MEMEDAR_MODEL_DAL_CARD_MAPPER_HPP
