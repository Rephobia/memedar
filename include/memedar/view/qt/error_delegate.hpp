#ifndef MEMEDAR_VIEW_QT_ERROR_DELEGATE_HPP
#define MEMEDAR_VIEW_QT_ERROR_DELEGATE_HPP


class QLabel;

namespace md::view::qt {
	class error_delegate;
}


#pragma GCC diagnostic ignored "-Weffc++"

class md::view::qt::error_delegate : public md::view::error_delegate
                                   , public md::view::qt::ui::box
{
public:
	error_delegate();
	void show_error(std::system_error &e) override;
	void show_error(QString message) override;
protected:
	QLabel* m_text;
};

#pragma GCC diagnostic pop


#endif // MEMEDAR_VIEW_QT_ERROR_DELEGATE_HPP
