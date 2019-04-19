#include <ctime>
#include <memory>

#include <boost/signals2.hpp>
#include <QString>
#include <QMainWindow>

#include "memedar/utils/storage.hpp"

#include "memedar/model/side/side.hpp"
#include "memedar/model/card/card.hpp"
#include "memedar/model/deck/deck.hpp"

#include "memedar/view/lobby.hpp"
#include "memedar/view/qt/ui/button.hpp"
#include "memedar/view/qt/ui/box.hpp"
#include "memedar/view/qt/main_window.hpp"
#include "memedar/view/qt/lobby.hpp"

using md::view::qt::lobby;

lobby::lobby(qt::main_window* main_window)
	: m_main_window {main_window}
{ ;}

void lobby::show(const utils::storage<model::deck::deck>& decks)
{
	auto box {new ui::box {QBoxLayout::TopToBottom}};

	for (decltype(auto) e : decks) {

		QString stat {e.name() +"\n" +
		              QString::number(e.noob_cards()) + "\n" +
		              QString::number(e.ready_cards()) + "\n" +
		              QString::number(e.delayed_cards()) + "\n" +
		              QString::number(e.total_cards())};

		auto btn {new ui::button {stat, [this, &e]()
		                                { go_to_lesson(e.id()); }}};
		auto designer {new ui::button {"add", [this, &e]()
		                                      { go_to_designer(e); }}};

		box->put_widget(QBoxLayout::LeftToRight, btn, designer);
	}

	m_main_window->set_widget(box);
}
