#include <QLabel>

#include "memedar/view/error_delegate.hpp"

#include "memedar/view/qt/ui/button.hpp"
#include "memedar/view/qt/ui/box.hpp"
#include "memedar/view/qt/error_delegate.hpp"


using md::view::qt::error_delegate;

error_delegate::error_delegate()
	: box      {QBoxLayout::TopToBottom}
	, m_text   {new QLabel {}}
{
	box::put_widget(m_text, new ui::button {"ok", [this]() { box::hide(); }});
}

void error_delegate::show_error(std::system_error &e)
{
	m_text->setText(e.what());
	box::show();
}

void error_delegate::show_error(QString message)
{
	m_text->setText(std::move(message));
	box::show();
}
