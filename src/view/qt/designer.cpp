#include <boost/signals2.hpp>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QMainWindow>

#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"

#include "memedar/view/qt/ui/button.hpp"
#include "memedar/view/qt/ui/box.hpp"
#include "memedar/view/qt/main_window.hpp"
#include "memedar/view/designer.hpp"
#include "memedar/view/qt/designer.hpp"


using md::view::qt::designer;

designer::designer(qt::main_window* main_window)
	: m_main_window {main_window}
{ ;}

void designer::show(const model::deck::deck& deck,
                    QString question, QString answer)
{
	auto label {new QLabel {deck.name()}};
	auto q_edit {new QTextEdit {question}};
	auto a_edit {new QTextEdit {answer}};
	auto typing {new QCheckBox {"typing"}};

	auto add_action {[this, &deck, q_edit, a_edit, typing]()
	                 {
		                 model::side::side q {q_edit->toPlainText()};
		                 model::side::side a {a_edit->toPlainText()};
		                 model::card::card card {std::move(q),
		                                         std::move(a),
		                                         typing->isChecked()};
		                 add_card(deck.id(), card);
	                 }};

	auto ok {new ui::button {"ok", add_action}};
	auto close {new ui::button {"close", [this]() { cancel(); }}};
	auto box {new ui::box {QBoxLayout::TopToBottom,
	                       label, typing, q_edit, a_edit}};
	box->put_widget(QBoxLayout::LeftToRight, ok, close);
	m_main_window->set_widget(box);
}

void designer::show()
{
	auto edit {new QLineEdit {}};

	auto add_action {[this, edit]()
	                 {
		                 model::deck::info info {edit->text()};
		                 model::deck::deck deck {std::move(info)};
		                 add_deck(deck);
	                 }};

	auto ok {new ui::button {"ok", add_action}};
	auto close {new ui::button {"close", [this]() { cancel(); }}};

	auto box {new ui::box {QBoxLayout::TopToBottom, edit}};
	box->put_widget(QBoxLayout::LeftToRight, ok, close);

	m_main_window->set_widget(box);
}
