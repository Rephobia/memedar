#include <boost/signals2.hpp>

#include "memedar/utils/storage.hpp"

#include "memedar/model/deck_service.hpp"

#include "memedar/view/lobby.hpp"
#include "memedar/presenter/lobby_presenter.hpp"


using md::lobby_presenter;

lobby_presenter::lobby_presenter(model::deck_service& deck_service,
                                 view::lobby& lobby)
	: m_deck_service {deck_service}
	, m_lobby        {lobby}
{
	m_lobby.go_to_lesson.connect([this](std::int64_t id)
	                             { go_to_lesson(id); });

	m_lobby.go_to_designer.connect([this](const md::model::deck::deck& deck)
	                               { go_to_designer(deck); });
}

void lobby_presenter::run()
{
	m_lobby.show(m_deck_service);
}
