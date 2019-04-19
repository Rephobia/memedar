#ifndef MEMEDAR_CONTROLLER_HPP
#define MEMEDAR_CONTROLLER_HPP


namespace md {
	class menu_presenter;
	class lobby_presenter;
	class designer_presenter;
	class lesson_presenter;
	class controller;
}


class md::controller
{
public:
	controller(md::menu_presenter& menu,
	           md::lobby_presenter& lobby,
	           md::designer_presenter& designer,
	           md::lesson_presenter& lesson);
protected:
	md::menu_presenter& m_menu;
	md::lobby_presenter& m_lobby;
	md::designer_presenter& m_designer;
	md::lesson_presenter& m_lesson;
};

#endif // MEMEDAR_CONTROLLER_HPP
