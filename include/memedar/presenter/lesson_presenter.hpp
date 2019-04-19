#ifndef LESSON_PRESENTER_HPP
#define LESSON_PRESENTER_HPP


class QString;

namespace md::model::task {
	class task_book;
}

namespace md::model {
	class deck_service;
	class task_service;
}

namespace md::view {
	class error_delegate;
}

namespace md::view {
	class lesson;
}

namespace md {
	class lesson_presenter;

}

class md::lesson_presenter
{
public:
	lesson_presenter(md::model::deck_service& deck_service,
	                 md::model::task_service& task_service,
	                 md::view::error_delegate& error_delegate,
	                 md::view::lesson& lesson);

	void run(std::int64_t deck_id);
	~lesson_presenter();
protected:
	void show_answer();
	void show_answer(const QString& answer);
	void again();
	void done(std::time_t gap);
protected:
	md::model::deck_service& m_deck_service;
	md::model::task_service& m_task_service;
	md::view::error_delegate& m_error_delegate;
	md::view::lesson& m_lesson;

	class body;
	std::unique_ptr<md::lesson_presenter::body> m_body;
};


#endif // LESSON_PRESENTER_HPP
