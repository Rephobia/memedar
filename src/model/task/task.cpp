#include <ctime>
#include <memory>

#include <QString>

#include "memedar/utils/ref_wrapper.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/task/task.hpp"

using md::model::task::task;

task::task(md::model::card::card& card, md::model::task::state state)
	: identity    {card.id()}
	, card        {card}
	, state       {state}
	, user_answer {QString {}}
{ ;}
