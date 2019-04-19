#ifndef MEMEDAR_VIEW_LOBBY_HPP
#define MEMEDAR_VIEW_LOBBY_HPP


namespace md::view {
	class lobby;
}


class md::view::lobby
{
public:
	virtual void show(const md::utils::storage<md::model::deck::deck>& decks) = 0;

	boost::signals2::signal<void(std::int64_t deck_id)> go_to_lesson {};
	boost::signals2::signal<void(const md::model::deck::deck& deck)> go_to_designer {};

	virtual ~lobby() = default;
};


#endif // MEMEDAR_VIEW_LOBBY_HPP
