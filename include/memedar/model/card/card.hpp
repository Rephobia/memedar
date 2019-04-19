#ifndef MEMEDAR_MODEL_CARD_CARD_HPP
#define MEMEDAR_MODEL_CARD_CARD_HPP


#include "memedar/model/identity.hpp"
#include "memedar/model/card/schedule.hpp"

namespace md::model::card {
	class type;
	class visitor;

	class card;
}

class md::model::card::card : public md::model::identity
                            , public md::model::card::schedule
{
public:
	card(md::model::side::side&& question,
	     md::model::side::side&& answer,
	     bool typing);

	card(md::model::identity id,
	     md::model::card::schedule schedule,
	     md::model::side::side&& question,
	     md::model::side::side&& answer,
	     bool typing);

	md::model::side::side question;
	md::model::side::side answer;

	bool has_typing() const;

	void set_type(std::shared_ptr<md::model::card::type> type);

	void take_visitor(md::model::card::visitor& visitor);
protected:
	bool m_typing;
	std::shared_ptr<md::model::card::type> m_type;
};


#endif // MEMEDAR_MODEL_CARD_CARD_HPP
