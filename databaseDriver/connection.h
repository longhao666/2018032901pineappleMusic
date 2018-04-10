#ifndef CONNECTION_H
#define CONNECTION_H

#include "databaseDriver_global.h"
class QSqlQuery;
class QString;


int logInUser(QSqlQuery &q, QString t1, QString t2);
void addUser(QSqlQuery &q, int t1, QString t2);
int entertUserAndPassword(QSqlQuery &q, QString t1, QString t2);
DATABASEDRIVERSHARED_EXPORT bool createConnection();



#endif // CONNECTION_H
