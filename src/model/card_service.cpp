#include <ctime>
#include <memory>

#include <QString>

#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"

#include "memedar/model/dal/transaction.hpp"
#include "memedar/model/dal/card_mapper.hpp"
#include "memedar/model/dal/transaction_guard.hpp"

#include "memedar/view/error_delegate.hpp"
#include "memedar/model/card_service.hpp"


using md::model::card_service;

card_service::card_service(md::view::error_delegate& error_delegate,
                           dal::transaction& transaction,
                           dal::card_mapper& card_mapper)
	: m_error_delegate {error_delegate}
	, m_transaction    {transaction}
	, m_card_mapper    {card_mapper}
{ ;}

void card_service::save_card(deck::deck& deck, card::card&& card)
{
	try {
		auto guard {dal::make_transaction(m_transaction)};

		if (deck.empty()) {
			m_card_mapper.load_cards(deck);
		}

		m_card_mapper.save_card(deck, std::move(card));

		guard.commit();
	}
	catch (std::system_error &e) {

		m_error_delegate.show_error(e);
	}
}
