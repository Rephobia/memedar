#include <memory>
#include <filesystem>

#include <sqlite3.h>
#include <QString>

#include "memedar/model/dal/transaction.hpp"
#include "memedar/model/dal/sqlite/adapter.hpp"
#include "memedar/model/dal/sqlite/transaction.hpp"

namespace res =  md::model::dal::sqlite::transaction_resources;

std::string res::begin_cmd()
{
	std::string cmd {"begin"};
	return cmd;
}

std::string res::commit_cmd()
{
	std::string cmd {"commit"};
	return cmd;
}

std::string res::rollback_cmd()
{
	std::string cmd {"rollback"};
	return cmd;
}


using md::model::dal::sqlite::transaction;
using md::model::dal::sqlite::adapter::connector;

transaction::transaction(md::model::dal::sqlite::adapter::handle& db)
	: m_db {db}
{ ;}

void transaction::begin()
{
	static connector conn {m_db, res::begin_cmd()};
	conn.step();
}

void transaction::commit()
{
	static connector conn {m_db, res::commit_cmd()};
	conn.step();
}

void transaction::rollback()
{
	static connector conn {m_db, res::rollback_cmd()};
	conn.step();
}
