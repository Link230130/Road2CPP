#include "RulerWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RulerWidget w;
    w.show();
    return a.exec();
}
