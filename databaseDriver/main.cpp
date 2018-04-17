#include "databasedriver.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    if(!createConnection()) {
        return -1;
    }
    QSqlDatabase db = QSqlDatabase::database("lh1");
    QSqlQuery query(db);
    query.exec("select * from user");
    while(query.next()) {
        qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
    }

    DatabaseDriver d;
    d.show();
    return a.exec();
}
