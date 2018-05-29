#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>


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
    qDebug() << "=================";
    query.exec("select * from songPath");
    while(query.next()) {
        qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
    }

    MainWindow w;
    w.close();

    return a.exec();
}
