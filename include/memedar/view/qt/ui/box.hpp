#ifndef MEMEDAR_VIEW_QT_UI_BOX_HPP
#define MEMEDAR_VIEW_QT_UI_BOX_HPP


#include <QBoxLayout>

namespace md::view::qt::ui {
	class box;
}


#pragma GCC diagnostic ignored "-Weffc++"

class md::view::qt::ui::box : public QWidget
{
public:
	template<class... W>
	box(QBoxLayout::Direction dir, W... widgets)
		: m_layout {new QBoxLayout {dir, this}}
	{
		this->put_widget(widgets...);
	}
	template<class... W>
	void put_widget(W... widgets)
	{
		[[maybe_unused]] auto unused =
			{true, ((void) m_layout->addWidget(widgets), true)... };
	}
	template<class... W>
	void set_widget(W... widgets)
	{
		while (auto w = findChild<QWidget*>()) {
			delete w;
		}
		this->put_widget(widgets...);
	}
	template<class... W>
	void put_widget(QBoxLayout::Direction dir, W... widgets)
	{
		this->put_widget(new md::view::qt::ui::box {dir, widgets...});
	}
	template<class... W>
	void set_widget(QBoxLayout::Direction dir, W... widgets)
	{
		while (auto w = findChild<QWidget*>()) {
			delete w;
		}
		this->put_widget(dir, widgets...);
	}
protected:
	QBoxLayout* m_layout;
};

#pragma GCC diagnostic pop


#endif // MEMEDAR_VIEW_QT_UI_BOX_HPP
