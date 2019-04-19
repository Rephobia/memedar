#ifndef MEMEDAR_MENU_PRESENTER_HPP
#define MEMEDAR_MENU_PRESENTER_HPP


namespace md::view {
	class menu;
}

namespace md {
	class menu_presenter;
}


class md::menu_presenter
{
public:
	explicit menu_presenter(md::view::menu& menu);
	boost::signals2::signal<void()> go_to_designer {};
protected:
	md::view::menu& m_menu;
};


#endif // MEMEDAR_MENU_PRESENTER_HPP
