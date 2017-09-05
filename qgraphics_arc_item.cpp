#include <QGraphicsEllipseItem>
#include <limits>
#include <cmath>
#include "qgraphics_arc_item.hpp"

QGraphicsArcItem::QGraphicsArcItem(std::tuple<double, double> center, std::tuple<double, double> start, double angle)
{
	double centx, centy, strtx, strty;
	centx = std::get<0>(center);
	centy = std::get<1>(center);
	strtx = std::get<0>(start);
	strty = std::get<1>(start);

	QLineF rad(centx, centy, strtx, strty);

	double pi = atan2(0, -1);
	double xPos = rad.x1() - rad.length();
	double yPos = rad.y1() - rad.length();
	double width = rad.length() * 2;
	double height = rad.length() * 2;
	double strtAng = 16 * rad.angle();
	double an = 16 * angle * 180 / pi;

	setStartAngle(strtAng);
	setSpanAngle(an);
	setRect(xPos, yPos, width, height);
}

void QGraphicsArcItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->drawArc(rect(), startAngle(), spanAngle());
}

