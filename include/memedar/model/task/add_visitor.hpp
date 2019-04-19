#ifndef MEMEDAR_MODEL_TASK_ADD_VISITOR_HPP
#define MEMEDAR_MODEL_TASK_ADD_VISITOR_HPP


namespace md::model::task {
	class add_visitor;
}

class md::model::task::add_visitor : public md::model::card::visitor
{
public:
	add_visitor(md::model::task::task_book& task_book,
	            md::model::card::card& card,
	            md::model::task::state state);

	void visit(md::model::card::noob_t& ref) override;
	void visit(md::model::card::ready_t& ref) override;
	void visit(md::model::card::delayed_t& ref) override;

	bool is_task() const;
protected:
	bool m_task_status;
	md::model::task::task_book& m_task_book;
	md::model::card::card& m_card;
	md::model::task::state m_state;
};


#endif // MEMEDAR_MODEL_TASK_ADD_VISITOR_HPP
