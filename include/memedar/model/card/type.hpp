#ifndef MEMEDAR_MODEL_CARD_TYPE_HPP
#define MEMEDAR_MODEL_CARD_TYPE_HPP


namespace md::model::card {
	class visitor;
	class type;

	class noob_t;
	class ready_t;
	class delayed_t;
}


class md::model::card::type
{
public:
	virtual void accept(md::model::card::visitor &v) = 0;
	virtual ~type() = default;
};


class md::model::card::noob_t : public md::model::card::type
{
public:
	void accept(md::model::card::visitor &v) override;
};


class md::model::card::ready_t : public md::model::card::type
{
public:
	void accept(md::model::card::visitor &v) override;
};


class md::model::card::delayed_t : public md::model::card::type
{
public:
	void accept(md::model::card::visitor &v) override;
};


#endif // MEMEDAR_MODEL_CARD_TYPE_HPP
