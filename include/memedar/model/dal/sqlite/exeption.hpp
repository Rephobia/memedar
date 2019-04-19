#ifndef MEMEDAR_MODEL_DAL_SQLITE_ADAPTER_EXEPTION_HPP
#define MEMEDAR_MODEL_DAL_SQLITE_ADAPTER_EXEPTION_HPP


namespace md::model::dal::sqlite::adapter {

	class sqlite_error_category;
	std::error_category& get_sqlite_category();

	class sqlite_exeption;
}


class md::model::dal::sqlite::adapter::sqlite_error_category
	: public std::error_category
{
public:
	const char* name() const noexcept override;
	std::string message(int ev) const override;
};


class md::model::dal::sqlite::adapter::sqlite_exeption
	: public std::system_error
{
public:
	sqlite_exeption(int code,
	                const char* errmsg,
	                const std::string& fn);
};


#endif // MEMEDAR_MODEL_DAL_SQLITE_ADAPTER_EXEPTION_HPP
