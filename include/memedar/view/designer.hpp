#ifndef MEMEDAR_VIEW_DESIGNER_HPP
#define MEMEDAR_VIEW_DESIGNER_HPP


namespace md::view {
	class designer;
}


class md::view::designer
{
public:
	virtual void show(const md::model::deck::deck& deck,
	                  QString question = QString {},
	                  QString answer = QString {}) = 0;
	virtual void show() = 0;

	boost::signals2::signal<void(std::int64_t deck_id,
	                             md::model::card::card& card)> add_card {};
	boost::signals2::signal<void(md::model::deck::deck& deck)> add_deck {};
	boost::signals2::signal<void()> cancel {};

	virtual ~designer() = default;
};


#endif // MEMEDAR_VIEW_DESIGNER_HPP
