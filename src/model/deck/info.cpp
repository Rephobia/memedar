#include <ctime>

#include <QString>

#include "memedar/model/deck/info.hpp"

using md::model::deck::info;

info::info(QString&& name)
	: m_name         {std::move(name)}
	, m_added        {std::time(nullptr)}
	, m_last_opening {0}
{ ;}

info::info(QString&& name, std::time_t added, std::time_t last_opening)
	: m_name         {std::move(name)}
	, m_added        {added}
	, m_last_opening {last_opening}
{ ;}

info::info(info&& other)
	: m_name         {std::move(other.m_name)}
	, m_added        {other.m_added}
	, m_last_opening {other.m_last_opening}
{ ;}

info& info::operator=(info&& other)
{
	if (this != &other) {
		m_name = std::move(other.m_name);
		m_added = other.m_added;
		m_last_opening = other.m_last_opening;
	}

	return *this;
}

const QString& info::name() const
{
	return m_name;
}

std::time_t info::added() const
{
	return m_added;
}

std::time_t info::last_opening() const
{
	return m_last_opening;
}

void info::change_last_opening(std::time_t timestamp)
{
	m_last_opening = timestamp;
}
