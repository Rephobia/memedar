#ifndef MEMEDAR_VIEW_QT_LESSON_HPP
#define MEMEDAR_VIEW_QT_LESSON_HPP


namespace md::view::qt::ui {
	class button;
}

namespace md::view::qt {
	class lesson;
}


#pragma GCC diagnostic ignored "-Weffc++"

class md::view::qt::lesson : public md::view::lesson
{
public:
	explicit lesson(md::view::qt::main_window* main_window);
	void show(const md::model::task::task& task,
	          const md::model::deck::deck& deck) override;
	class painter;
protected:
	md::view::qt::main_window* m_main_window;
};

#pragma GCC diagnostic pop

class md::view::qt::lesson::painter : public md::view::qt::ui::box
{
public:
	painter(const md::model::deck::deck& deck,
	         md::view::qt::lesson& lesson);
	void draw(const md::model::task::task& task);
protected:
	void answering_state(const md::model::card::card& card);
	void answering_state_input(const md::model::card::card& card);
	void marking_state(const md::model::task::task& task);
	void done_state(const md::model::card::card& card);
protected:
	const md::model::deck::deck& m_deck;
	md::view::qt::lesson& m_lesson;
};


#endif // MEMEDAR_VIEW_QT_LESSON_HPP
