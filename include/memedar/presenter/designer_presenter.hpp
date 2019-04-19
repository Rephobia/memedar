#ifndef MEMEDAR_DESIGNER_PRESENTER_HPP
#define MEMEDAR_DESIGNER_PRESENTER_HPP


namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
}
namespace md::model {
	class card_service;
	class deck_service;
}

namespace md::view {
	class error_delegate;
	class designer;
}

namespace md {
	class designer_presenter;
}


class md::designer_presenter
{
public:
	designer_presenter(md::model::deck_service& deck_service,
	                   md::model::card_service& card_service,
	                   md::view::error_delegate& error_delegate,
	                   md::view::designer& designer);

	boost::signals2::signal<void()> cancel {};

	void run(const md::model::deck::deck& deck);
	void run();
protected:
	void add_card(std::int64_t deck_id, md::model::card::card&& card);
	void add_deck(md::model::deck::deck&& deck);
protected:
	md::model::deck_service& m_deck_service;
	md::model::card_service& m_card_service;
	md::view::error_delegate& m_error_delegate;
	md::view::designer& m_designer;
};


#endif // MEMEDAR_DESIGNER_PRESENTER_HPP
