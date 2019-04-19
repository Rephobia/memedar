#ifndef MEMEDAR_MODEL_DAL_SQLITE_CARD_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_SQLITE_CARD_MAPPER_HPP


namespace md::model::side {
	class side;
}

namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
}

namespace md::model::dal::sqlite {
	class side_index;
	class card_mapper;
}


class md::model::dal::sqlite::card_mapper : public md::model::dal::card_mapper
{
public:
	explicit card_mapper(md::model::dal::sqlite::adapter::handle& db);

	void create_table() override;

	void save_card(md::model::deck::deck& deck,
	               md::model::card::card&& card) override;
	void load_cards(md::model::deck::deck& deck) override;

	void update_repeat(md::model::card::card& card, std::time_t repeat) override;
	void reset_combo(md::model::card::card& card) override;
protected:
	void save_side(md::model::side::side& side);
	md::model::side::side read_side(md::model::dal::sqlite::adapter::connector& conn,
	                                md::model::dal::sqlite::side_index ind);
protected:
	md::model::dal::sqlite::adapter::handle& m_db;
};


#endif // MEMEDAR_MODEL_DAL_SQLITE_CARD_MAPPER_HPP
