#ifndef MESSAGE_WIDGET_HPP_
#define MESSAGE_WIDGET_HPP_

#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>

class MessageWidget : public QWidget
{
Q_OBJECT
public:
	MessageWidget(QWidget * parent = nullptr);
public slots:
	void info(QString message);
	void error(QString message);
private:
	QHBoxLayout* layout;
	QLineEdit* line;

};


#endif