#ifndef MEMEDAR_MODEL_DAL_TRANSACTION_HPP
#define MEMEDAR_MODEL_DAL_TRANSACTION_HPP


namespace md::model::dal {
	class transaction;
}

class md::model::dal::transaction
{
public:
	virtual void begin() = 0;
	virtual void commit() = 0;
	virtual void rollback() = 0;
	virtual ~transaction() = default;
};


#endif // MEMEDAR_MODEL_DAL_TRANSACTION_HPP
