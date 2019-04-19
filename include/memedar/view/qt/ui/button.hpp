#ifndef MEMEDAR_VIEW_QT_UI_BUTTON_HPP
#define MEMEDAR_VIEW_QT_UI_BUTTON_HPP

#include <QPushButton>

namespace md::view::qt::ui {
	class button;
}


class md::view::qt::ui::button : public QPushButton
{
public:
	template<class... A>
	button(QString text, A... actions)
	{
		this->setText(text);
		this->attach(actions...);
	}
	template<class... A>
	void attach(A... actions)
	{
		[[maybe_unused]] auto unused =
			{true, ((void) this->tie(actions), true)...};
	}

protected:
	template<class Lambda>
	void tie(Lambda lambda)
	{
		QObject::connect(this, &QPushButton::clicked, lambda);
	}
	void tie(const QKeySequence& shortcut)
	{
		this->setShortcut(shortcut);
	}
};


#endif // MEMEDAR_VIEW_QT_UI_BUTTON_HPP
