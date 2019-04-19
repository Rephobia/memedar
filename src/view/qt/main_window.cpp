#include <QMainWindow>
#include <QScrollArea>

#include "memedar/view/qt/main_window.hpp"


using md::view::qt::main_window;

main_window::main_window()
	: m_main_area {new QScrollArea {}}
{
	m_main_area->setWidgetResizable(true);
}

void main_window::set_widget(QWidget* new_widget)
{
	auto old_widget = m_main_area->takeWidget();

	m_main_area->setWidget(new_widget);

	if (old_widget) {
		old_widget->deleteLater();
	}
	else {
		this->setCentralWidget(m_main_area);
	}
}
