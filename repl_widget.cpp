#include <QLineEdit>
#include <QLayout>
#include <QLabel>
#include <QObject>
#include <QKeyEvent>

#include <iostream>

#include "repl_widget.hpp"

REPLWidget::REPLWidget(QWidget * parent) : QWidget(parent)
{
	histIndex = 0;

	auto layout = new QHBoxLayout;

	line = new QLineEdit(this);
	QLabel* label = new QLabel;
	label->setText("vtscript> ");

	layout->addWidget(label);
	layout->addWidget(line);
	
	setLayout(layout);
	setMaximumHeight(50);


	QObject::connect(line, &QLineEdit::returnPressed, this, &REPLWidget::pressedReturn);
}

void REPLWidget::pressedReturn()
{
	QString qLine = line->text();
	line->clear();
	history.push_back(qLine);
	histIndex = 0;
	emit lineEntered(qLine);
}

void REPLWidget::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Up)
	{
		if ((histIndex < history.size())) {
			histIndex++;
		}
		if (!history.empty()){
			line->setText(history[history.size() - histIndex]);
		}
	}
	else if (event->key() == Qt::Key_Down)
	{
		if (histIndex > 0) {
			histIndex--;
		}
		if (histIndex == 0 && !history.empty()) {
			line->setText("");
		}
		else if (!history.empty()) {
			line->setText(history[history.size() - histIndex]);
		}
	}
}
