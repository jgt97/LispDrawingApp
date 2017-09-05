#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>

#include <iostream>

#include "canvas_widget.hpp"

CanvasWidget::CanvasWidget(QWidget * parent) : QWidget(parent)
{
	auto layout = new QVBoxLayout;

	
	canvas = new QGraphicsView(this);
	scene = new QGraphicsScene(canvas);
	canvas->setScene(scene);
	painter = new QPainter;

	layout->addWidget(canvas);

	setLayout(layout);
	setMinimumHeight(300);
}

void CanvasWidget::addGraphic(QGraphicsItem * item)
{
	scene->addItem(item);
	scene->update();
}