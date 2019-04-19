#ifndef MEMEDAR_MODEL_DAL_SQLITE_DECK_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_SQLITE_DECK_MAPPER_HPP


namespace md::model::deck {
	class deck;
}

namespace md::model::dal::sqlite {
	class deck_mapper;
}


class md::model::dal::sqlite::deck_mapper : public md::model::dal::deck_mapper
{
public:
	explicit deck_mapper(md::model::dal::sqlite::adapter::handle& db);

	void create_table() override;

	md::utils::storage<md::model::deck::deck> load_decks() override;
	void save_deck(md::model::deck::deck& deck) override;

	void decrement_daily_noob(md::model::deck::deck& deck) override;
	void decrement_daily_ready(md::model::deck::deck& deck) override;
	void reset_daily(md::model::deck::deck& deck) override;
	void update_last_opening(md::model::deck::deck& deck) override;
protected:
	md::model::dal::sqlite::adapter::handle& m_db;
};


#endif // MEMEDAR_MODEL_DAL_SQLITE_DECK_MAPPER_HPP
