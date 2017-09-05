#ifndef CANVAS_WIDGET_HPP_
#define CANVAS_WIDGET_HPP_

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsView>

class CanvasWidget : public QWidget
{
Q_OBJECT
public:
	CanvasWidget(QWidget * parent = nullptr);
public slots:
	void addGraphic(QGraphicsItem * item);
private:
	QGraphicsView* canvas;
	QGraphicsScene* scene;
	QPainter* painter;
};


#endif