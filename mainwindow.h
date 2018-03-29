#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databaseDriver/databasedriver.h"
#include "musicPlayer/player.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotEnterWidget();
    void slotMusicWidget();
    void slotPlayerShow();
    void slotWidgetClost();

private:
    Ui::MainWindow *ui;
    DatabaseDriver *databaseDriver;
    Player *player;
    QPushButton *p1;
};

#endif // MAINWINDOW_H
