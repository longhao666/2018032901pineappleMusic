#include "connection.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QTime>
#include <QSqlRecord>

QString getRandomId();

bool createConnection()
{
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE","lh1");
    db1.setDatabaseName("my1.db");
    if(!db1.open()) {
        QMessageBox::critical(0,
                              "Cannot open database",
                              "Unable to establish a database connetion",
                              QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query1(db1);
#if 0
    if(!query1.exec("create table user (id char primary key, "
                    "username char unique, "
                    "password char) ")) {
        qDebug() << query1.lastError();
    }
#endif
#if 1
    if(!query1.exec("create table user (id char check(length(id) between 0 and 30) primary key, "
                    "username char check(length(username) between 5 and 15) unique, "
                    "password char check(length(password) between 6 and 6)) ")) {
        qDebug() << query1.lastError();
    }
    if(!query1.exec("insert into user values (20180418, '123456', '123456');")) {
        qDebug() << query1.lastError();
    }
#endif

#if 0
    if(!query1.exec("create table student (id int primary key,name char(20));")) {
        qDebug() << query1.lastError();
    }
#if 1
    if(!query1.exec("insert into student values (0, 'LiMing');")) {
        qDebug() << query1.lastError();
    }
    if(!query1.exec("insert into student values (1, 'LongHao')")) {
        qDebug() << query1.lastError();
    }
#endif
#endif
    return true;
}

#if 1
void addUser(QSqlQuery &q, int t1, QString t2) {
    q.prepare("insert into student(id, name) values(?,?)");
    q.addBindValue(t1);
    q.addBindValue(t2);
    if(!q.exec()) {
        qDebug() << q.lastError() << "addUser";
    }
}
#endif

int logInUser(QSqlQuery &q, QString t1, QString t2) {
    if(t1 == "") {
        return 1;
    }
    if(t2 == "") {
        return 2;
    }
    QString s = getRandomId();
    q.prepare("insert into user(id, username, password) values(?,?,?)");
    q.addBindValue(s);
    q.addBindValue(t1);
    q.addBindValue(t2);
    if(!q.exec()) {
        qDebug() << q.lastError() << "logInUser";
        return 4;
    }
    return 0;
}

QString getRandomId()
{
//    qDebug() << QTime::currentTime();
//    qDebug() << QDateTime::currentDateTime();
    return QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
}

int entertUserAndPassword(QSqlQuery &q, QString t1, QString t2)
{
    if(t1 == "" || t2 == "") {
        return 1;
    }
    QString s = QString("select * from user where username='%1' and password='%2';").arg(t1).arg(t2);
#if 0
    qDebug() << s;
    qDebug()<< t1 << t2;
#endif
    if(!q.exec(s)) {
        qDebug() << q.lastError();
        return -1;
    }
    while(q.next()) {
#if 0
        qDebug() << q.value(0).toString() << q.value(1).toString() << q.value(2).toString() << q.at();
#endif
        return 0;
    }
    return 4;
}
