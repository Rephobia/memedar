#ifndef MEMEDAR_MODEL_TASK_TASK_HPP
#define MEMEDAR_MODEL_TASK_TASK_HPP


#include "memedar/model/identity.hpp"

namespace md::model::task {
	class task;
	enum class state : int { answering = 0, marking, done };

}


class md::model::task::task : public md::model::identity
{
public:
	task(md::model::card::card& card, md::model::task::state state);

	md::utils::ref_wrapper<md::model::card::card> card;
	md::model::task::state state;
	QString user_answer;
};


#endif // MEMEDAR_MODEL_TASK_TASK_HPP
