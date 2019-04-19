#ifndef MEMEDAR_VIEW_QT_MENU_HPP
#define MEMEDAR_VIEW_QT_MENU_HPP


namespace md::view::qt {
	class menu;
}


class md::view::qt::menu : public md::view::menu
{
public:
	explicit menu(md::view::qt::main_window* main_window);
};


#endif // MEMEDAR_VIEW_QT_MENU_HPP
