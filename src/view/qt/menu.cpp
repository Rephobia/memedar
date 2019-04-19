#include <boost/signals2.hpp>
#include <QMainWindow>
#include <QApplication>

#include "memedar/view/menu.hpp"
#include "memedar/view/qt/ui/button.hpp"
#include "memedar/view/qt/ui/box.hpp"
#include "memedar/view/qt/main_window.hpp"
#include "memedar/view/qt/menu.hpp"


using md::view::qt::menu;

menu::menu(qt::main_window* main_window)
{
	auto quit     {new ui::button {"quit", []() { ::QApplication::quit(); }}};
	auto designer {new ui::button {"add deck", [this]() { go_to_designer(); }}};

	auto box {new ui::box {QBoxLayout::LeftToRight, quit, designer}};

	main_window->setMenuWidget(box);
}
