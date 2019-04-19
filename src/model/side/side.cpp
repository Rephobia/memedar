#include <cstdint>

#include <QString>

#include "memedar/model/side/side.hpp"

using md::model::side::side;

side::side(QString&& text)
	: identity {identity {}}
	, m_text   {std::move(text)}
{ ;}
side::side(identity id, QString&& text)
	: identity {id}
	, m_text   {std::move(text)}
{ ;}

side::side(side&& other)
	: identity {static_cast<identity>(other)}
	, m_text   {std::move(other.m_text)}
{ ;}

side& side::operator=(side&& other)
{
	if (this != &other) {
		identity::operator=(static_cast<identity>(other));
		m_text = std::move(other.m_text);
	}
	return *this;
}

const QString& side::text() const
{
	return m_text;
}
