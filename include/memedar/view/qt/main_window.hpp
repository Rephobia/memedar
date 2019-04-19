#ifndef MEMEDAR_VIEW_QT_MAIN_WINDOW_HPP
#define MEMEDAR_VIEW_QT_MAIN_WINDOW_HPP


class QScrollArea;

namespace md::view::qt {
	class main_window;
}


#pragma GCC diagnostic ignored "-Weffc++"

class md::view::qt::main_window : public QMainWindow
{
public:
	main_window();
	void set_widget(QWidget* new_widget);
protected:
	QScrollArea* m_main_area;
};

#pragma GCC diagnostic pop


#endif // MEMEDAR_VIEW_QT_MAIN_WINDOW_HPP
