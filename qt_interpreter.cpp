#include <QGraphicsItem>
#include <sstream>
#include<fstream>

#include <iostream>

#include "qt_interpreter.hpp"
#include "interpreter.hpp"
#include "interpreter_semantic_error.hpp"
#include "qgraphics_arc_item.hpp"


QtInterpreter::QtInterpreter(QObject * parent) : QObject(parent)
{
}

void QtInterpreter::draw()
{
	if (graphicCache.empty())
	{
		return;
	}
	for (auto it : graphicCache) {
		std::string type = it.getType();
		if (type == "Point") {
			QGraphicsEllipseItem* item = new QGraphicsEllipseItem;
			std::tuple<double, double> pt = it.getPtVal();
			double x = std::get<0>(pt);
			double y = std::get<1>(pt);
			double radius = 2;
			item->setRect(x - radius, y - radius, radius * 2, radius * 2);
			item->setBrush(QColor(Qt::black));
			emit drawGraphic(item);
		}
		else if (type == "Line") {
			QGraphicsLineItem* item = new QGraphicsLineItem;
			std::tuple<double, double> start = it.getLinStrtVal();
			std::tuple<double, double> end = it.getLinEndVal();
			double x1 = std::get<0>(start);
			double y1 = std::get<1>(start);
			double x2 = std::get<0>(end);
			double y2 = std::get<1>(end);
			item->setLine(x1, y1, x2, y2);
			emit drawGraphic(item);
		}
		else if (type == "Arc") {
			std::tuple<double, double> center = it.getArcCntrVal();
			std::tuple<double, double> start = it.getArcStrtVal();
			double angle = it.getArcAnglVal();
			QGraphicsArcItem* item = new QGraphicsArcItem(center, start, angle);
			emit drawGraphic(item);
		}
		
	}
}

void QtInterpreter::parseAndEvaluate(QString entry)
{
	std::stringstream program;
	program << entry.toStdString();

	Expression result;
	QString qOut;
	if (repl.parse(program)) {
		try {
			result = repl.eval();
		}
		catch (InterpreterSemanticError& errorMes)
		{
			QString errorOut = errorMes.what();
			emit error(errorOut);
			return;
		}
		if (repl.hasDraw()) {
			graphicCache = repl.getGraphicContainer();
			draw();
		}
		std::string output = repl.outputExp(result);
		qOut = QString::fromStdString(output);
		emit info(qOut);
	}
	else {
		qOut = "Error: parse error";
		emit error(qOut);
	}
}

void QtInterpreter::evalFile(std::ifstream& in)
{
	Expression result;
	QString qOut;
	if (repl.parse(in)) {
		try {
			result = repl.eval();
		}
		catch (InterpreterSemanticError& errorMes)
		{
			QString errorOut = errorMes.what();
			emit error(errorOut);
			return;
		}
		if (repl.hasDraw()) {
			graphicCache = repl.getGraphicContainer();
			draw();
		}
		std::string output = repl.outputExp(result);
		qOut = QString::fromStdString(output);
		qOut.remove("\n");
		emit info(qOut);
	}
	else {
		qOut = "Error: parse error";
		emit error(qOut);
	}
}