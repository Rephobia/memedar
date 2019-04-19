#ifndef MEMEDAR_UTILS_REF_WRAPPER_HPP
#define MEMEDAR_UTILS_REF_WRAPPER_HPP


namespace md::utils {
	template <class T>
	class ref_wrapper;
}


template <class T>
class md::utils::ref_wrapper
{
public:
	explicit ref_wrapper(T& ref)
		:   m_ref {ref}
	{ ;}
	explicit ref_wrapper(const std::reference_wrapper<T>& ref)
		:   m_ref {ref}
	{ ;}

	operator const T& () const noexcept
	{
		return m_ref.get();
	}

	operator T& () noexcept
	{
		return m_ref.get();
	}

	const T& get() const noexcept
	{
		return m_ref.get();
	}

	T& get() noexcept
	{
		return m_ref.get();
	}
protected:
	std::reference_wrapper<T> m_ref;
};


#endif // MEMEDAR_UTILS_REF_WRAPPER_HPP
