#ifndef REPL_WIDGET_HPP_
#define REPL_WIDGET_HPP_

#include <QWidget>
#include <QKeyEvent>
#include <QLineEdit>
#include <string>
#include <vector>

class REPLWidget : public QWidget
{
Q_OBJECT
public:
	REPLWidget(QWidget * parent = nullptr);
signals:
	void lineEntered(QString);
public slots:
	void pressedReturn();
private:
	QLineEdit* line;
	std::vector<QString> history;
	void keyPressEvent(QKeyEvent *event);
	unsigned int histIndex;
};

#endif

