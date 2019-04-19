#ifndef MEMEDAR_MODEL_DECK_INFO_HPP
#define MEMEDAR_MODEL_DECK_INFO_HPP


namespace md::model::deck {
	class info;
}


class md::model::deck::info
{
public:
	explicit info(QString&& name);
	info(QString&& name, std::time_t added, std::time_t last_opening);

	info(md::model::deck::info&& other);
	md::model::deck::info& operator=(md::model::deck::info&& other);

	info(const md::model::deck::info& other) = delete;
	md::model::deck::info& operator=(const md::model::deck::info& other) = delete;

	const QString& name() const;

	std::time_t added() const;

	std::time_t last_opening() const;
	void change_last_opening(std::time_t timestamp);
protected:
	QString m_name;
	std::time_t m_added;
	std::time_t m_last_opening;
};


#endif // MEMEDAR_MODEL_DECK_INFO_HPP
