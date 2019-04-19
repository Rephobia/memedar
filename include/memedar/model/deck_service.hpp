#ifndef MEMEDAR_MODEL_DECK_SERVICE_HPP
#define MEMEDAR_MODEL_DECK_SERVICE_HPP


namespace md::model::deck {
	class deck;
}

namespace md::model::dal {
	class transaction;
	class card_mapper;
	class deck_mapper;
}

namespace md::view {
	class error_delegate;
}

namespace md::model {
	class deck_service;
}


class md::model::deck_service : public md::utils::storage<md::model::deck::deck>
{
public:
	deck_service(md::view::error_delegate& error_delegate,
	             md::model::dal::transaction& transaction,
	             md::model::dal::card_mapper& card_mapper,
	             md::model::dal::deck_mapper& deck_mapper);

	void save_deck(md::model::deck::deck&& deck);
protected:
	void load_decks();
protected:
	md::view::error_delegate& m_error_delegate;
	md::model::dal::transaction& m_transaction;
	md::model::dal::card_mapper& m_card_mapper;
	md::model::dal::deck_mapper& m_deck_mapper;
};


#endif // MEMEDAR_MODEL_DECK_SERVICE_HPP
