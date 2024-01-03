#include "stdafx.h"
#include "TrafficJam.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrafficJam w;
    w.show();
    return a.exec();
}
