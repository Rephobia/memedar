#ifndef MEMEDAR_VIEW_ERROR_DELEGATE_HPP
#define MEMEDAR_VIEW_ERROR_DELEGATE_HPP


namespace md::view {
	class error_delegate;
}


class md::view::error_delegate
{
public:
	virtual void show_error(std::system_error &e) = 0;
	virtual void show_error(QString message) = 0;
	virtual ~error_delegate() = default;
};


#endif // MEMEDAR_VIEW_ERROR_DELEGATE_HPP
