#ifndef MEMEDAR_MODEL_CARD_SERVICE_HPP
#define MEMEDAR_MODEL_CARD_SERVICE_HPP


namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
}

namespace md::model::dal {
	class transaction;
	class card_mapper;
}

namespace md::model {
	class card_service;
}

namespace md::view {
	class error_delegate;
}


class md::model::card_service
{
public:
	card_service(md::view::error_delegate& error_delegate,
	             md::model::dal::transaction& transaction,
	             md::model::dal::card_mapper& card_mapper);

	void save_card(md::model::deck::deck& deck, md::model::card::card&& card);
protected:
	md::view::error_delegate& m_error_delegate;
	md::model::dal::transaction& m_transaction;
	md::model::dal::card_mapper& m_card_mapper;
};


#endif // MEMEDAR_MODEL_CARD_SERVICE_HPP
