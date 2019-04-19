#ifndef MEMEDAR_LOBBY_PRESENTER_HPP
#define MEMEDAR_LOBBY_PRESENTER_HPP


namespace md::model::deck {
	class deck;
}

namespace md::model {
	class deck_service;
}


namespace md::view {
	class lobby;
}

namespace md {
	class lobby_presenter;
}

class md::lobby_presenter
{
public:
	lobby_presenter(md::model::deck_service& deck_service,
	                md::view::lobby& lobby);
	void run();
	boost::signals2::signal<void(std::int64_t deck_id)> go_to_lesson {};
	boost::signals2::signal<void(const md::model::deck::deck& deck)> go_to_designer {};
protected:
	md::model::deck_service& m_deck_service;
	md::view::lobby& m_lobby;
};


#endif // MEMEDAR_LOBBY_PRESENTER_HPP
