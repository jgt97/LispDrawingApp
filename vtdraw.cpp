#include <QApplication>

#include "main_window.hpp"
#include "repl_widget.hpp"
#include "message_widget.hpp"
#include "canvas_widget.hpp"

#include <string>

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	MainWindow* window;

	if (argc > 1) {
		std::string file = argv[1];
		window = new MainWindow(file);;
	}
	else {
		window = new MainWindow;
	}

	window->show();

	return app.exec();
}