#ifndef DATABASEDRIVER_H
#define DATABASEDRIVER_H

#include "databaseDriver_global.h"
#include "connection.h"
#include <QWidget>

namespace Ui {
class databaseDriver;
}

class DATABASEDRIVERSHARED_EXPORT DatabaseDriver : public QWidget
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

protected:
    void paintEvent(QPaintEvent *event);

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
