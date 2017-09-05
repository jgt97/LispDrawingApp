#include <QLayout>
#include <QWidget>
#include <QObject>
#include <fstream>

#include "main_window.hpp"
#include "repl_widget.hpp"
#include "message_widget.hpp"
#include "canvas_widget.hpp"
#include "qt_interpreter.hpp"

MainWindow::MainWindow(QWidget * parent) : QWidget(parent)
{
	auto layout = new QVBoxLayout;

	MessageWidget* message = new MessageWidget;
	layout->addWidget(message);

	CanvasWidget* canvas = new CanvasWidget;
	layout->addWidget(canvas);

	REPLWidget* repl = new REPLWidget(this);
	layout->addWidget(repl);

	QObject::connect(repl, &REPLWidget::lineEntered, &interp, &QtInterpreter::parseAndEvaluate);
	QObject::connect(&interp, &QtInterpreter::info, message, &MessageWidget::info);
	QObject::connect(&interp, &QtInterpreter::error, message, &MessageWidget::error);
	QObject::connect(&interp, &QtInterpreter::drawGraphic, canvas, &CanvasWidget::addGraphic);

	

	setLayout(layout);
	setMinimumSize(800, 600);

}

MainWindow::MainWindow(std::string filename, QWidget * parent) : QWidget(parent)
{
	auto layout = new QVBoxLayout;

	MessageWidget* message = new MessageWidget;
	layout->addWidget(message);

	CanvasWidget* canvas = new CanvasWidget;
	layout->addWidget(canvas);

	REPLWidget* repl = new REPLWidget(this);
	layout->addWidget(repl);

	QObject::connect(repl, &REPLWidget::lineEntered, &interp, &QtInterpreter::parseAndEvaluate);
	QObject::connect(&interp, &QtInterpreter::info, message, &MessageWidget::info);
	QObject::connect(&interp, &QtInterpreter::error, message, &MessageWidget::error);
	QObject::connect(&interp, &QtInterpreter::drawGraphic, canvas, &CanvasWidget::addGraphic);

	file = filename;
	std::ifstream in(file);
	interp.evalFile(in);

	setLayout(layout);
	setMinimumSize(800, 600);
}