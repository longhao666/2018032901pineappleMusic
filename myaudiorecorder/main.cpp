#include "myRecorderWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyRecorderWidget w;
    w.show();

    return a.exec();
}
