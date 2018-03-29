#include "connection.h"

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
#if 1
    if(!query1.exec("create table user (id char(30) primary key, "
                    "user char(20) unique, "
                    "password char(20))")) {
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

bool logInUser(QSqlQuery &q, QString t1, QString t2) {
    if(t1 == "" || t2 == "") {
        return false;
    }
    QString s = getRandomId();
    q.prepare("insert into user(id, user, password) values(?,?,?)");
    q.addBindValue(s);
    q.addBindValue(t1);
    q.addBindValue(t2);
    if(!q.exec()) {
        qDebug() << q.lastError() << "logInUser";
        return false;
    }
    return true;
}

QString getRandomId()
{
//    qDebug() << QTime::currentTime();
//    qDebug() << QDateTime::currentDateTime();
    return QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
}

bool entertUserAndPassword(QSqlQuery &q, QString t1, QString t2)
{
    if(t1 == "" || t2 == "") {
        return false;
    }
    QString s = QString("select * from user where user='%1' and password='%2';").arg(t1).arg(t2);
#if 0
    qDebug() << s;
    qDebug()<< t1 << t2;
#endif
    if(!q.exec(s)) {
        qDebug() << q.lastError();
        return false;
    }
    while(q.next()) {
#if 0
        qDebug() << q.value(0).toString() << q.value(1).toString() << q.value(2).toString() << q.at();
#endif
        return true;
    }
    return false;
}
