#ifndef MEMEDAR_MODEL_TASK_SERVICE_HPP
#define MEMEDAR_MODEL_TASK_SERVICE_HPP


namespace md::model::deck {
	class deck;
}

namespace md::model::task {
	class task;
}

namespace md::model::dal {
	class card_mapper;
	class deck_mapper;
	class task_mapper;
	class transaction;
}

namespace md::view {
	class error_delegate;
}

namespace md::model {
	class task_service;
}


class md::model::task_service
{
public:
	task_service(md::view::error_delegate& error_delegate,
	             md::model::dal::transaction& transaction,
	             md::model::dal::card_mapper& card_mapper,
	             md::model::dal::deck_mapper& deck_mapper,
	             md::model::dal::task_mapper& task_mapper);

	md::model::task::task_book make_task(md::model::deck::deck& deck);

	void again_card(md::model::task::task& task);
	void done_card(md::model::deck::deck& deck, md::model::task::task& task, std::time_t gap);
protected:
	class done_visitor;
protected:
	md::view::error_delegate& m_error_delegate;
	md::model::dal::transaction& m_transaction;
	md::model::dal::card_mapper& m_card_mapper;
	md::model::dal::deck_mapper& m_deck_mapper;
	md::model::dal::task_mapper& m_task_mapper;
};


#endif // MEMEDAR_MODEL_TASK_SERVICE_HPP
