#include <string>

#include "memedar/model/dal/sqlite/task_mapper_resources.hpp"


using md::model::dal::sqlite::task_index;
namespace res = md::model::dal::sqlite::task_resources;


std::string res::create_table()
{
	std::string cmd {"create table if not exists tasks("
	                 "card_id integer primary key,"
	                 "deck_id integer,"
	                 "state integer,"
	                 "foreign key (card_id) references cards(id),"
	                 "foreign key (deck_id) references decks(id));"};
	return cmd;
}

std::string res::insert_cmd()
{
	std::string cmd {"insert into tasks("
	                 "card_id, deck_id, state)"
	                 "values (?1, ?2, ?3);"};

	return cmd;
}

task_index res::insert_index()
{
	task_index ind {};
	ind.set_card_id(1);
	ind.set_deck_id(2);
	ind.set_state(3);
	return ind;
}

std::string res::select_cmd()
{
	std::string cmd {"select * from tasks where deck_id = ?1;"};
	return cmd;
}

task_index res::select_index()
{
	task_index ind {};
	ind.set_card_id(0);
	ind.set_deck_id(1);
	ind.set_state(2);
	return ind;
}

std::string res::change_state_cmd()
{
	std::string cmd {"update tasks set state = ?1 where card_id = ?2;"};
	return cmd;
}

task_index res::change_state_index()
{
	task_index ind {};
	ind.set_state(1);
	ind.set_card_id(2);
	return ind;
}

std::string res::delete_done_cmd()
{
	std::string cmd {"delete from tasks where deck_id = ?1 and state = ?2;"};
	return cmd;
}

task_index res::delete_done_index()
{
	task_index ind {};
	ind.set_deck_id(1);
	ind.set_state(2);
	return ind;
}
