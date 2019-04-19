#ifndef MEMEDAR_MODEL_DAL_SQLITE_TRANSACTION_HPP
#define MEMEDAR_MODEL_DAL_SQLITE_TRANSACTION_HPP


namespace md::model::dal::sqlite {
	namespace transaction_resources {
		std::string begin_cmd();
		std::string commit_cmd();
		std::string rollback_cmd();
	}
	class transaction;
}


class md::model::dal::sqlite::transaction : public md::model::dal::transaction
{
public:
	explicit transaction(md::model::dal::sqlite::adapter::handle& db);
	void begin() override;
	void commit() override;
	void rollback() override;
protected:
	md::model::dal::sqlite::adapter::handle& m_db;
};


#endif // MEMEDAR_MODEL_DAL_SQLITE_TRANSACTION_HPP
