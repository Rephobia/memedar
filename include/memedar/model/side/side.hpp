#ifndef MEMEDAR_MODEL_SIDE_SIDE_HPP
#define MEMEDAR_MODEL_SIDE_SIDE_HPP


#include "memedar/model/identity.hpp"

namespace md::model::side {
	class side;
}


class md::model::side::side : public md::model::identity
{
public:
	explicit side(QString&& text);
	side(md::model::identity id, QString&& text);
	side(md::model::side::side&& other);
	side(const md::model::side::side& other) = delete;

	md::model::side::side& operator=(md::model::side::side&& other);
	md::model::side::side& operator=(const md::model::side::side& other) = delete;

	const QString& text() const;
protected:
	QString m_text;
};


#endif // MEMEDAR_MODEL_SIDE_SIDE_HPP
