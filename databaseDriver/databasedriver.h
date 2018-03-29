#ifndef DATABASEDRIVER_H
#define DATABASEDRIVER_H

#include <QWidget>
#include "connection.h"


namespace Ui {
class databaseDriver;
}

class DatabaseDriver : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseDriver(QWidget *parent = 0);
    ~DatabaseDriver();

signals:
    void signalEnterClicked();
    void signalLogInClicked();
    void signalQuitClicked();
    void signalForgetClicked();

private slots:
    void slotLogInClicked();
    void slotQuitClicked();
    void slotEnterClicked();
    void slotForgetClicked();

private:
    Ui::databaseDriver *ui;
    QSqlQuery *query;
};

#endif // DATABASEDRIVER_H
