#ifndef MEMEDAR_MODEL_DAL_TASK_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_TASK_MAPPER_HPP


namespace md::model::deck {
	class deck;
}

namespace md::model::task {
	enum class state : int;
	class task;
	class task_book;
}

namespace md::model::dal {
	class task_mapper;
}


class md::model::dal::task_mapper
{
public:
	virtual void create_table() = 0;

	virtual	void save_task(const md::model::deck::deck& deck,
		               const md::model::task::task& task) = 0;
	virtual void load_task_book(md::model::task::task_book& task_book) = 0;

	virtual void change_state(md::model::task::task& task, md::model::task::state state) = 0;
	virtual void delete_done_task(md::model::deck::deck& deck) = 0;

	virtual ~task_mapper() = default;
};


#endif // MEMEDAR_MODEL_DAL_TASK_MAPPER_HPP
