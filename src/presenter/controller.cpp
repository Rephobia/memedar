#include <ctime>
#include <boost/signals2.hpp>

#include "memedar/presenter/menu_presenter.hpp"
#include "memedar/presenter/lobby_presenter.hpp"
#include "memedar/presenter/designer_presenter.hpp"
#include "memedar/presenter/lesson_presenter.hpp"
#include "memedar/presenter/controller.hpp"


using md::controller;

controller::controller(md::menu_presenter& menu,
                       md::lobby_presenter& lobby,
                       md::designer_presenter& designer,
                       md::lesson_presenter& lesson)
	: m_menu     {menu}
	, m_lobby    {lobby}
	, m_designer {designer}
	, m_lesson   {lesson}
{
	m_menu.go_to_designer.connect([this]() { m_designer.run(); });

	m_lobby.go_to_lesson.connect([this](std::int64_t id)
	                             { m_lesson.run(id); });

	m_lobby.go_to_designer.connect([this](const md::model::deck::deck& deck)
	                               { m_designer.run(deck); });

	m_designer.cancel.connect([this]() { m_lobby.run(); });
	m_lobby.run();
}
