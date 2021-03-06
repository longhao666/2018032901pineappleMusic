#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection()) {
        return 1;
    }
    QSqlDatabase db = QSqlDatabase::database("lh1");
    QSqlQuery query(db);

    query.exec("select * from user");
    while(query.next()) {
        qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
    }
    MainWindow w;
    w.show();

    return a.exec();
}
