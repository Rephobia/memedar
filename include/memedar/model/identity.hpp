#ifndef MEMEDAR_MODEL_IDENTITY_HPP
#define MEMEDAR_MODEL_IDENTITY_HPP


namespace md::model {
	class identity;
}


class md::model::identity
{
public:
	explicit identity(std::int64_t id = 0) : m_id {id} { ;}
	std::int64_t id() const { return m_id; }
protected:
	std::int64_t m_id;
};


#endif // MEMEDAR_MODEL_IDENTITY_HPP
