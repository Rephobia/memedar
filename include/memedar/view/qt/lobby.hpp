#ifndef MEMEDAR_VIEW_QT_LOBBY_HPP
#define MEMEDAR_VIEW_QT_LOBBY_HPP


namespace md::view::qt {
	class lobby;
}


#pragma GCC diagnostic ignored "-Weffc++"

class md::view::qt::lobby : public md::view::lobby
{
public:
	explicit lobby(md::view::qt::main_window* main_window);
	void show(const md::utils::storage<md::model::deck::deck>& decks) override;
protected:
	md::view::qt::main_window* m_main_window;
};

#pragma GCC diagnostic pop


#endif // MEMEDAR_VIEW_QT_LOBBY_HPP
