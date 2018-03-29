#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QTime>
#include <QSqlRecord>


bool createConnection();
bool logInUser(QSqlQuery &q, QString t1, QString t2);
void addUser(QSqlQuery &q, int t1, QString t2);
bool entertUserAndPassword(QSqlQuery &q, QString t1, QString t2);



#endif // CONNECTION_H
