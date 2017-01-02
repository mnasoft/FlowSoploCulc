#include <QApplication>
#include "Flow.h"

///Проект FlowSoploCulc позволяет рассчитать расход через сопло.
int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	Flow * mainWin = new Flow;
	mainWin->show();
	return app.exec();
}
