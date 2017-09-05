#ifndef QGRAPHICS_ARC_ITEM_HPP_
#define QGRAPHICS_ARC_ITEM_HPP_

#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QWidget>
#include <tuple>

#include "canvas_widget.hpp"

class QGraphicsArcItem : public QGraphicsEllipseItem
{
public:
	QGraphicsArcItem(std::tuple<double, double> center, std::tuple<double, double> start, double angle);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

private:
	std::tuple<double, double> cent;
	std::tuple<double, double> strt;
	double angl;
	CanvasWidget* cnvs;
	QGraphicsEllipseItem* ellipse;

};

#endif