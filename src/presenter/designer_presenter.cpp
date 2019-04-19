#include <ctime>
#include <boost/signals2.hpp>

#include <QString>

#include "memedar/utils/find.hpp"
#include "memedar/utils/storage.hpp"

#include "memedar/model/deck/deck.hpp"
#include "memedar/model/card_service.hpp"
#include "memedar/model/deck_service.hpp"

#include "memedar/view/error_delegate.hpp"
#include "memedar/view/designer.hpp"
#include "memedar/presenter/designer_presenter.hpp"

using md::designer_presenter;


designer_presenter::designer_presenter(model::deck_service& deck_service,
                                       model::card_service& cards_service,
                                       view::error_delegate& error_delegate,
                                       view::designer& designer)
	: m_deck_service   {deck_service}
	, m_card_service   {cards_service}
	, m_error_delegate {error_delegate}
	, m_designer       {designer}
{
	m_designer.add_card.connect([this](std::int64_t id, model::card::card& card)
	                            { add_card(id, std::move(card)); });

	m_designer.add_deck.connect([this](model::deck::deck& deck)
	                            { add_deck(std::move(deck)); });

	m_designer.cancel.connect([this]() { cancel(); });
}

void designer_presenter::run(const model::deck::deck& deck)
{
	m_designer.show(deck);
}

void designer_presenter::run()
{
	m_designer.show();
}

void designer_presenter::add_card(std::int64_t id, model::card::card&& card)
{
	auto deck_it {utils::find_by_id(id, m_deck_service)};

	if (deck_it != m_deck_service.end()) {
		m_card_service.save_card(*deck_it, std::move(card));
	}
	else {
		m_error_delegate.show_error("deck (id: "
		                           + QString::number(id)
		                           + ") doesn't exists");
	}
}

void designer_presenter::add_deck(model::deck::deck&& deck)
{
	m_deck_service.save_deck(std::move(deck));
	cancel();
}
