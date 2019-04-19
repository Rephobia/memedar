#ifndef MEMEDAR_MODEL_DAL_SQLITE_TASK_MAPPER_HPP
#define MEMEDAR_MODEL_DAL_SQLITE_TASK_MAPPER_HPP


namespace md::model::card {
	class card;
}

namespace md::model::deck {
	class deck;
}

namespace md::model::task {
	class task;
	class task_book;
}

namespace md::model::dal::sqlite {
	class task_mapper;
}

class md::model::dal::sqlite::task_mapper : public md::model::dal::task_mapper
{
public:
	explicit task_mapper(md::model::dal::sqlite::adapter::handle& db);

	void create_table() override;

	void save_task(const md::model::deck::deck& deck,
	               const md::model::task::task& task) override;
	void load_task_book(md::model::task::task_book& task_book) override;

	void change_state(md::model::task::task& task, md::model::task::state state) override;
	void delete_done_task(md::model::deck::deck& deck) override;
protected:
	md::model::dal::sqlite::adapter::handle& m_db;
};


#endif // MEMEDAR_MODEL_DAL_SQLITE_TASK_MAPPER_HPP
