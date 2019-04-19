#ifndef MEMEDAR_VIEW_LESSON_HPP
#define MEMEDAR_VIEW_LESSON_HPP


namespace md::view {
	class lesson;
}


class md::view::lesson
{
public:
	virtual void show(const md::model::task::task& task,
	                  const md::model::deck::deck& deck) = 0;


	boost::signals2::signal<void()> prev_task {};
	boost::signals2::signal<void()> next_task {};

	boost::signals2::signal<void(const md::model::task::task& task)> re_draw {};
	boost::signals2::signal<void()> answer {};
	boost::signals2::signal<void(const QString& answer)> answer_text {};
	boost::signals2::signal<void()> again {};
	boost::signals2::signal<void(std::time_t gap)> done {};

	virtual ~lesson() = default;
};


#endif // MEMEDAR_VIEW_LESSON_HPP
