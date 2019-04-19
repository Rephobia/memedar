#include <memory>
#include <iostream>

#include "memedar/model/dal/transaction.hpp"
#include "memedar/model/dal/transaction_guard.hpp"


using md::model::dal::transaction;
using md::model::dal::transaction_guard;

transaction_guard md::model::dal::make_transaction(transaction& transaction)
{
	return transaction_guard {transaction};
}

transaction_guard::transaction_guard(transaction& transaction)
	: m_commited    {false}
	, m_transaction {transaction}
{
	m_transaction.begin();
}

void transaction_guard::commit()
{
	m_transaction.commit();
	m_commited = true;
}

transaction_guard::~transaction_guard()
{
	try {
		if (not m_commited) {
			m_transaction.rollback();
		}
	}
	catch (std::runtime_error &e) {

		std::cout << e.what() << std::endl;
	}
}
