#include <QLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPalette>

#include "message_widget.hpp"

MessageWidget::MessageWidget(QWidget * parent) : QWidget(parent)
{
	layout = new QHBoxLayout;

	line = new QLineEdit(this);
	line->setReadOnly(true);

	QLabel* label = new QLabel;
	label->setText("Message: ");

	layout->addWidget(label);
	layout->addWidget(line);

	setLayout(layout);
}

void MessageWidget::info(QString message)
{
	QPalette p;
	line->setPalette(p);
	line->setText(message);
}

void MessageWidget::error(QString message)
{
	QPalette p = line->palette();
	p.setColor(QPalette::Highlight, QColor(Qt::red));
	line->setPalette(p);
	line->setText(message);
	line->selectAll();
}
