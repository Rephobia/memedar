#ifndef MEMEDAR_MODEL_DAL_SQLITE_ADAPTER_HPP
#define MEMEDAR_MODEL_DAL_SQLITE_ADAPTER_HPP


namespace md::model::dal::sqlite::adapter {

	namespace detail {

		struct handle_deleter
		{
			void operator()(sqlite3* ptr) const
			{
				::sqlite3_close(ptr);
			}
		};

		struct stmt_deleter
		{
			void operator()(sqlite3_stmt* stmt) const
			{
				::sqlite3_finalize(stmt);
			}
		};

		QString convert_to_qstring(const unsigned char *str);
	}

	using handle = std::unique_ptr<sqlite3, detail::handle_deleter>;
	using statement = std::unique_ptr<sqlite3_stmt, detail::stmt_deleter>;

	class connector;

	template<typename T>
	class binder;

	handle open_sqlite(const std::filesystem::path& path);
	statement prepare_sqlite(const handle& db, const std::string& sqlCmd);

	int step(const handle& db, const statement& statement);
}

class md::model::dal::sqlite::adapter::connector
{
public:
	connector(handle& db, const std::string& sql_cmd);

	void bind(const int index, const std::int64_t value);
	void bind(const int index, const QString& value,
	          sqlite3_destructor_type destructor);

	int step();

	template<typename ...B>
	void exec_bind(B... b)
	{
		[[maybe_unused]] auto unused =
			{true, ((void) b.bind(*this), true)...};

		adapter::step(m_db, m_stmt);
		::sqlite3_reset(m_stmt.get());
	}

	std::int64_t read_int64t(const int index);
	QString read_string(const int index);
protected:
	handle& m_db;
	statement m_stmt;
};


template<typename T>
class md::model::dal::sqlite::adapter::binder
{
public:
	binder(int index, const T value,
	       [[maybe_unused]] sqlite3_destructor_type destructor = nullptr)
		: m_index {index}
		, m_value {value}
	{ ;}
	void bind(md::model::dal::sqlite::adapter::connector& conn)
	{
		conn.bind(m_index, m_value);
	}
private:
	int m_index;
	T m_value;
};


template <>
class md::model::dal::sqlite::adapter::binder<QString>
{
public:
	binder(int index, const QString& value,
	       sqlite3_destructor_type destructor = SQLITE_STATIC)
		: m_index {index}
		, m_value {value}
		, m_destructor {destructor}
	{ ;}
	void bind(md::model::dal::sqlite::adapter::connector& conn)
	{
		conn.bind(m_index, m_value, m_destructor);
	}
private:
	int m_index;
	QString m_value;
	sqlite3_destructor_type m_destructor;
};


#endif  // MEMEDAR_MODEL_DAL_SQLITE_ADAPTER_HPP
