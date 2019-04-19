#ifndef MEMEDAR_MODEL_CARD_VISITOR_HPP
#define MEMEDAR_MODEL_CARD_VISITOR_HPP


namespace md::model::card {
	class visitor;

	class noob_t;
	class ready_t;
	class delayed_t;
}

class md::model::card::visitor
{
public:
	virtual void visit(md::model::card::noob_t& ref) = 0;
	virtual void visit(md::model::card::ready_t& ref) = 0;
	virtual void visit(md::model::card::delayed_t& ref) = 0;

	virtual ~visitor() = default;
};


#endif // MEMEDAR_MODEL_CARD_VISITOR_HPP
