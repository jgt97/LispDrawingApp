#include <QDebug>
#include <QtTest/QtTest>
#include <QtWidgets>

#include "canvas_widget.hpp"
#include "main_window.hpp"
#include "message_widget.hpp"
#include "repl_widget.hpp"

// ADD YOUR TESTS TO THIS CLASS !!!!!!!
class TestGUI : public QObject {
  Q_OBJECT

public:
private slots:

  void initTestCase();
  void testREPLGood();
  void testREPLBad();
  void testREPLBad2Good();
  void testPoint();
  void testLine();
  void testArc();
  void testEnvRestore();

  void testDefinePt();
  void testDefineLine();
  void testDefineArc();
  void testMessageWidget();
  void testCanvasWidget();
  void testREPLBadParse();
  void testHistory();

private:
  MainWindow w;

  REPLWidget *repl;
  QLineEdit *replEdit;
  MessageWidget *message;
  QLineEdit *messageEdit;
  CanvasWidget *canvas;
  QGraphicsScene *scene;
};

void TestGUI::initTestCase() {

  repl = w.findChild<REPLWidget *>();
  QVERIFY2(repl, "Could not find REPLWidget instance in MainWindow instance.");

  replEdit = repl->findChild<QLineEdit *>();
  QVERIFY2(replEdit,
           "Could not find QLineEdit instance in REPLWidget instance.");

  message = w.findChild<MessageWidget *>();
  QVERIFY2(message,
           "Could not find MessageWidget instance in MainWindow instance.");

  messageEdit = message->findChild<QLineEdit *>();
  QVERIFY2(messageEdit,
           "Could not find QLineEdit instance in MessageWidget instance.");

  canvas = w.findChild<CanvasWidget *>();
  QVERIFY2(canvas,
           "Could not find CanvasWidget instance in MainWindow instance.");

  scene = canvas->findChild<QGraphicsScene *>();
  QVERIFY2(scene,
           "Could not find QGraphicsScene instance in CanvasWidget instance.");
}

void TestGUI::testREPLGood() {

  QVERIFY(repl && replEdit);
  QVERIFY(message && messageEdit);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(define a 1)");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check message
  QVERIFY2(messageEdit->isReadOnly(),
           "Expected QLineEdit inside MessageWidget to be read-only.");
  QCOMPARE(messageEdit->text(), QString("(1)"));
}

void TestGUI::testREPLBad() {

  QVERIFY(repl && replEdit);
  QVERIFY(message && messageEdit);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(foo)");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check message
  QVERIFY2(messageEdit->isReadOnly(),
           "Expected QLineEdit inside MessageWidget to be read-only.");
  QVERIFY2(messageEdit->text().startsWith("Error"), "Expected error message.");

  // check background color and selection
  QPalette p = messageEdit->palette();
  QCOMPARE(p.highlight().color(), QColor(Qt::red));
  QVERIFY2(messageEdit->selectedText().startsWith("Error"),
           "Expected error to be selected.");
}

void TestGUI::testREPLBad2Good() {

  QVERIFY(repl && replEdit);
  QVERIFY(message && messageEdit);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(foo)");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check message
  QVERIFY2(messageEdit->isReadOnly(),
           "Expected QLineEdit inside MessageWidget to be read-only.");
  QVERIFY2(messageEdit->text().startsWith("Error"), "Expected error message.");

  // check background color and selection
  QPalette p = messageEdit->palette();
  QCOMPARE(p.highlight().color(), QColor(Qt::red));
  QVERIFY2(messageEdit->selectedText().startsWith("Error"),
           "Expected error to be selected.");

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(define value 100)");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check message
  QVERIFY2(messageEdit->isReadOnly(),
           "Expected QLineEdit inside MessageWidget to be read-only.");
  QCOMPARE(messageEdit->text(), QString("(100)"));

  // check background color and selection
  p = messageEdit->palette();
  QVERIFY2(p.highlight().color() != QColor(Qt::red),
           "Did not expect red highlight on successful eval.");
  QVERIFY2(messageEdit->selectedText() == "",
           "Expected no selcted text on successful eval.");
}

void TestGUI::testPoint() {

  QVERIFY(repl && replEdit);
  QVERIFY(canvas && scene);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(draw (point 0 0))");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check canvas
  QVERIFY2(scene->itemAt(QPointF(0, 0), QTransform()) != 0,
           "Expected a point in the scene. Not found.");
}

void TestGUI::testLine() {

  QVERIFY(repl && replEdit);
  QVERIFY(canvas && scene);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(draw (line (point 10 0) (point 0 10)))");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
  
  // check canvas
  QVERIFY2(scene->itemAt(QPointF(10, 0), QTransform()) != 0,
           "Expected a line in the scene. Not found.");
  QVERIFY2(scene->itemAt(QPointF(0, 10), QTransform()) != 0,
           "Expected a line in the scene. Not found.");
}

void TestGUI::testArc() {

  QVERIFY(repl && replEdit);
  QVERIFY(canvas && scene);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(draw (arc (point 0 0) (point 100 0) pi))");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check canvas
  QVERIFY2(scene->itemAt(QPointF(100, 0), QTransform()) != 0,
           "Expected a point on the arc in the scene. Not found.");
  QVERIFY2(scene->itemAt(QPointF(-100, 0), QTransform()) != 0,
           "Expected a point on the arc in the scene. Not found.");
}

void TestGUI::testEnvRestore() {

  QVERIFY(repl && replEdit);
  QVERIFY(canvas && scene);

  // send a string to the repl widget
  QTest::keyClicks(replEdit, "(begin (draw (point -20 0)) (define pi 3))");
  QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

  // check canvas
  QVERIFY2(scene->itemAt(QPointF(-20, 0), QTransform()) == 0,
           "Did not expected a point in the scene. One found.");
}

void TestGUI::testDefinePt() {

	QVERIFY(repl && replEdit);
	QVERIFY(message && messageEdit);

	// send a string to the repl widget
	QTest::keyClicks(replEdit, "(define pt (point 0 0))");
	QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

	// check message
	QVERIFY2(messageEdit->isReadOnly(),
		"Expected QLineEdit inside MessageWidget to be read-only.");
	QCOMPARE(messageEdit->text(), QString("(0,0)"));
}

void TestGUI::testDefineLine() {

	QVERIFY(repl && replEdit);
	QVERIFY(message && messageEdit);

	// send a string to the repl widget
	QTest::keyClicks(replEdit, "(define ln (line (point 0 0) (point 100 100)))");
	QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

	// check message
	QVERIFY2(messageEdit->isReadOnly(),
		"Expected QLineEdit inside MessageWidget to be read-only.");
	QCOMPARE(messageEdit->text(), QString("((0,0)(100,100))"));
}

void TestGUI::testDefineArc() {

	QVERIFY(repl && replEdit);
	QVERIFY(message && messageEdit);

	// send a string to the repl widget
	QTest::keyClicks(replEdit, "(define myArc (arc (point 0 0) (point 100 100) 2))");
	QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

	// check message
	QVERIFY2(messageEdit->isReadOnly(),
		"Expected QLineEdit inside MessageWidget to be read-only.");
	QCOMPARE(messageEdit->text(), QString("((0,0)(100,100) 2)"));
}

void TestGUI::testMessageWidget() {

	MessageWidget mes;
	mes.info("TEST");
	QLineEdit* line = mes.findChild<QLineEdit* >();

	// check message
	QVERIFY2(line->isReadOnly(),
		"Expected QLineEdit inside MessageWidget to be read-only.");
	QCOMPARE(line->text(), QString("TEST"));

	mes.error("TEST ERROR");
	// check message
	QVERIFY2(line->isReadOnly(),
		"Expected QLineEdit inside MessageWidget to be read-only.");
	QCOMPARE(line->text(), QString("TEST ERROR"));
}

void TestGUI::testCanvasWidget() {

	CanvasWidget can;
	QGraphicsLineItem line;
	line.setLine(0, 0, 5, 5);
	can.addGraphic(&line);

	QGraphicsScene* sce = can.findChild<QGraphicsScene* >();
	QVERIFY2(sce->itemAt(QPointF(5, 5), QTransform()) != 0,
		"Expected a point on the line in the scene. Not found.");
}

void TestGUI::testREPLBadParse() {
	QVERIFY(repl && replEdit);
	QVERIFY(message && messageEdit);

	// send a string to the repl widget
	QTest::keyClicks(replEdit, "(foo");
	QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

	// check message
	QVERIFY2(messageEdit->isReadOnly(),
		"Expected QLineEdit inside MessageWidget to be read-only.");
	QVERIFY2(messageEdit->text().startsWith("Error"), "Expected error message.");

	// check background color and selection
	QPalette p = messageEdit->palette();
	QCOMPARE(p.highlight().color(), QColor(Qt::red));
	QVERIFY2(messageEdit->selectedText().startsWith("Error"),
		"Expected error to be selected.");
}

void TestGUI::testHistory() {
	QVERIFY(repl && replEdit);
	QVERIFY(message && messageEdit);

	// send a string to the repl widget
	QTest::keyClicks(replEdit, "(define a 1)");
	QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);
	QTest::keyClicks(replEdit, "(define b 2)");
	QTest::keyClick(replEdit, Qt::Key_Return, Qt::NoModifier);

	QTest::keyClick(replEdit, Qt::Key_Up, Qt::NoModifier);
	QCOMPARE(replEdit->text(), QString("(define b 2)"));
	QTest::keyClick(replEdit, Qt::Key_Up, Qt::NoModifier);
	QCOMPARE(replEdit->text(), QString("(define a 1)"));
	QTest::keyClick(replEdit, Qt::Key_Down, Qt::NoModifier);
	QCOMPARE(replEdit->text(), QString("(define b 2)"));
	QTest::keyClick(replEdit, Qt::Key_Down, Qt::NoModifier);
	QCOMPARE(replEdit->text(), QString(""));
}


QTEST_MAIN(TestGUI)
#include "test_gui.moc"