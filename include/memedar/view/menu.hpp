#ifndef MEMEDAR_VIEW_MENU_HPP
#define MEMEDAR_VIEW_MENU_HPP


namespace md::view {
	class menu;
}


class md::view::menu
{
public:
	boost::signals2::signal<void()> go_to_designer {};

	virtual ~menu() = default;
};


#endif // MEMEDAR_VIEW_MENU_HPP
