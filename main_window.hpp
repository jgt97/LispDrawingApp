#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <QWidget>

#include "qt_interpreter.hpp"

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget * parent = nullptr);

	MainWindow(std::string filename, QWidget * parent = nullptr);
private:
	QtInterpreter interp;
	std::string file;
};

#endif