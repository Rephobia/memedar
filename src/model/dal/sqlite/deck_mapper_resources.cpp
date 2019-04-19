#include <string>

#include "memedar/model/dal/sqlite/deck_mapper_resources.hpp"


using md::model::dal::sqlite::deck_index;
namespace res = md::model::dal::sqlite::deck_resources;


std::string res::create_cmd()
{
	std::string cmd {"create table if not exists decks("
	                 "id integer primary key asc,"
	                 "deck_name text unique,"
	                 "added integer,"
	                 "last_opening integer,"
	                 "max_noob_cards integer,"
	                 "max_ready_cards integer,"
	                 "daily_noob_cards integer,"
	                 "daily_ready_cards integer,"
	                 "good_gap integer,"
	                 "easy_gap integer,"
	                 "good_ratio integer,"
	                 "easy_ratio integer"
	                 ");"};
	return cmd;
}

std::string res::insert_cmd()
{
	std::string cmd {"insert into decks("
	                 "deck_name, added, last_opening,"
	                 "max_noob_cards, max_ready_cards,"
	                 "daily_noob_cards, daily_ready_cards,"
	                 "good_gap, easy_gap, good_ratio, easy_ratio"
	                 ")"
	                 "values (?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, ?9, ?10, ?11);"};
	return cmd;
}

deck_index res::insert_index()
{
	deck_index ind {};
	ind.set_name(1);
	ind.set_added(2);
	ind.set_last_opening(3);

	ind.set_max_noob_cards(4);
	ind.set_max_ready_cards(5);
	ind.set_daily_noob_cards(6);
	ind.set_daily_ready_cards(7);

	ind.set_good_gap(8);
	ind.set_easy_gap(9);
	ind.set_good_ratio(10);
	ind.set_easy_ratio(11);

	return ind;
}

std::string res::select_cmd()
{
	std::string cmd {"select d.id, d.deck_name, d.added, d.last_opening,"
	                 "d.max_noob_cards, d.max_ready_cards,"
	                 "d.daily_noob_cards, d.daily_ready_cards,"
	                 "d.good_gap, d.easy_gap, d.good_ratio, d.easy_ratio,"
	                 "sum(case when c.repeat = 0 then 1 else 0 end) as noob_cards,"
	                 "sum(case when c.repeat != 0 and c.repeat < ?1 then 1 else 0 end) "
	                 "as ready_cards, "
	                 "sum(case when c.repeat != 0 and c.repeat > ?1 then 1 else 0 end) "
	                 "as delayed_cards "
	                 "from decks as d "
	                 "left join cards as c on d.id = c.deck_id group by d.id;"};
	return cmd;
}

deck_index res::select_index()
{
	deck_index ind {};
	ind.set_id(0);

	ind.set_name(1);
	ind.set_added(2);
	ind.set_last_opening(3);

	ind.set_max_noob_cards(4);
	ind.set_max_ready_cards(5);
	ind.set_daily_noob_cards(6);
	ind.set_daily_ready_cards(7);

	ind.set_good_gap(8);
	ind.set_easy_gap(9);
	ind.set_good_ratio(10);
	ind.set_easy_ratio(11);

	ind.set_noob_cards(12);
	ind.set_ready_cards(13);
	ind.set_delayed_cards(14);

	ind.set_timestamp(1);

	return ind;
}

std::string res::decrement_daily_noob_cmd()
{
	std::string cmd {"update decks set daily_noob_cards = daily_noob_cards - 1 "
	                 "where id = ?1;"};

	return cmd;
}

std::string res::decrement_daily_ready_cmd()
{
	std::string cmd {"update decks set daily_ready_cards = daily_ready_cards - 1 "
	                 "where id = ?1;"};

	return cmd;
}

deck_index res::decrement_daily_index()
{
	deck_index ind {};
	ind.set_id(1);
	return ind;
}

std::string res::update_opening_cmd()
{
	std::string cmd {"update decks set last_opening = ?1 where id = ?2;"};

	return cmd;
}

deck_index res::update_opening_index()
{
	deck_index ind {};
	ind.set_last_opening(1);
	ind.set_id(2);
	return ind;
}

std::string res::reset_daily_cmd()
{
	std::string cmd {"update decks set daily_noob_cards = ?1, "
	                 "daily_ready_cards = ?2 "
	                 "where id = ?3;"};
	return cmd;
}

deck_index res::reset_daily_index()
{
	deck_index ind {};
	ind.set_daily_noob_cards(1);
	ind.set_daily_ready_cards(2);
	ind.set_id(3);
	return ind;
}