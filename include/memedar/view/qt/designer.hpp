#ifndef MEMEDAR_VIEW_QT_DESIGNER_HPP
#define MEMEDAR_VIEW_QT_DESIGNER_HPP


namespace md::model::deck {
	class deck;
}

namespace md::view::qt {
	class designer;
}


#pragma GCC diagnostic ignored "-Weffc++"

class md::view::qt::designer : public md::view::designer
{
public:
	explicit designer(md::view::qt::main_window* main_window);

	void show(const md::model::deck::deck& deck,
	          QString question = QString {},
	          QString answer = QString {}) override;

	void show() override;
protected:
	md::view::qt::main_window* m_main_window;
};

#pragma GCC diagnostic pop


#endif // MEMEDAR_VIEW_QT_DESIGNER_HPP
