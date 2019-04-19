#ifndef MEMEDAR_UTILS_FIND_HPP
#define MEMEDAR_UTILS_FIND_HPP


namespace md::utils {
	template<class T>
	class storage;
}

namespace md::utils {

	template<class T>
	typename utils::storage<T>::iterator
	find_by_id(std::int64_t id, utils::storage<T>& storage)
	{
		auto find {[id, &storage](const T& obj)
		           { return obj.id() == id; }};

		return std::find_if(storage.begin(), storage.end(), find);
	}
	template<class T>
	typename utils::storage<std::unique_ptr<T>>::iterator
	find_by_id(std::int64_t id, utils::storage<std::unique_ptr<T>>& storage)
	{
		auto find {[id, &storage](const std::unique_ptr<T>& obj)
		           { return obj->id() == id; }};

		return std::find_if(storage.begin(), storage.end(), find);
	}
}


#endif // MEMEDAR_UTILS_FIND_HPP
