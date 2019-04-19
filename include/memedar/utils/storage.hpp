#ifndef MEMEDAR_UTILS_STORAGE_HPP
#define MEMEDAR_UTILS_STORAGE_HPP


#include <vector>

namespace md::utils {
	template<class T>
	class storage;
}


template<class T>
class md::utils::storage
{
public:
	using container = std::vector<T>;
	using iterator = typename container::iterator;
	using const_iterator = typename container::const_iterator;

	storage() = default;

	storage(const storage& other) = delete;
	storage operator=(const storage& other) = delete;

	storage(storage&& other)
		: m_storage {std::move(other.m_storage)}
	{ ;}

	storage& operator=(storage&& other)
	{
		if (this != &other) {
			m_storage = std::move(other.m_storage);
		}
		return *this;
	}

	iterator begin()
	{
		return m_storage.begin();
	}

	iterator end()
	{
		return m_storage.end();
	}

	const_iterator begin() const
	{
		return m_storage.begin();
	}

	const_iterator end() const
	{
		return m_storage.end();
	}

	T& back()
	{
		return m_storage.back();
	}

	const T& back() const
	{
		return m_storage.back();
	}

	// typename container::size_type size() const
	// {
		// return m_storage.size();
	// }

	bool empty() const
	{
		return m_storage.empty();
	}

	void add(T&& value)
	{
		m_storage.push_back(std::forward<T>(value));
	}
private:
	container m_storage {container {}};
};


#endif // MEMEDAR_UTILS_STORAGE_HPP
