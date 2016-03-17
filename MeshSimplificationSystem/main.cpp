#include "meshsimplificationsystem.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MeshSimplificationSystem w;
	w.show();
	return a.exec();
}
