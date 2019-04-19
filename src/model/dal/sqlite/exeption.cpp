#include <system_error>

#include <sqlite3.h>

#include "memedar/model/dal/sqlite/exeption.hpp"


using md::model::dal::sqlite::adapter::sqlite_error_category;

const char* sqlite_error_category::name() const noexcept
{
	return "sqlite3";
}

std::string sqlite_error_category::message(int ev) const
{
	if (const char* errorString {::sqlite3_errstr(ev)}) {
		return errorString;
	}
	return "unknown sqlite3 error";
}

std::error_category& md::model::dal::sqlite::adapter::get_sqlite_category()
{
	static sqlite_error_category s_category;
	return s_category;
}

using md::model::dal::sqlite::adapter::sqlite_exeption;

sqlite_exeption::sqlite_exeption(int code,
                                 const char* errmsg,
                                 const std::string& fn)
	: std::system_error {code, get_sqlite_category(),
	                     errmsg + std::string{" when calling "} + fn}
{ ;}
