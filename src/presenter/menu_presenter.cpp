#include <boost/signals2.hpp>

#include "memedar/presenter/menu_presenter.hpp"
#include "memedar/view/menu.hpp"

using md::menu_presenter;

menu_presenter::menu_presenter(md::view::menu& menu)
	: m_menu {menu}
{
	m_menu.go_to_designer.connect([this]() { go_to_designer(); });
}
