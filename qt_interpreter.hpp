#ifndef QT_INTERPRETER_HPP_
#define QT_INTERPRETER_HPP_

#include <QObject>
#include <QGraphicsItem>
#include <fstream>

#include "message_widget.hpp"
#include "interpreter.hpp"
#include "qgraphics_arc_item.hpp"
#include <canvas_widget.hpp>

class QtInterpreter : public QObject
{
Q_OBJECT
public:
	QtInterpreter(QObject * parent = nullptr);

	void draw();

	void evalFile(std::ifstream& in);
signals:

	void drawGraphic(QGraphicsItem * item);

	void info(QString message);

	void error(QString message);

public slots:
	void parseAndEvaluate(QString entry);
private:
	Interpreter repl;
	std::vector<Expression> graphicCache;

};


#endif