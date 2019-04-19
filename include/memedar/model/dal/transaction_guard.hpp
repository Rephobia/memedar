#ifndef MEMEDAR_MODEL_DAL_TRANSACTION_GUARD_HPP
#define MEMEDAR_MODEL_DAL_TRANSACTION_GUARD_HPP


namespace md::model::dal {
	class transaction;
	class transaction_guard;
	transaction_guard make_transaction(transaction& transaction);
}


class md::model::dal::transaction_guard
{
public:
	explicit transaction_guard(md::model::dal::transaction& transaction);

	void commit();

	~transaction_guard();
protected:
	bool m_commited;
	md::model::dal::transaction& m_transaction;
};


#endif // MEMEDAR_MODEL_DAL_TRANSACTION_GUARD_HPP
