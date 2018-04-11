#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasedriver.h"
#include "player.h"


class MusicPlayer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void signalMainWidgetChange(int select = 0);

private slots:
    void slotEnterWidget();
    void slotMusicWidget();
    void slotPlayerShow();
    void slotWidgetClost();
    void slotMusicAction();
    void slotMVAction();

private:
    Ui::MainWindow *ui;
    DatabaseDriver *databaseDriver;
    Player *player;
    QPushButton *p1;
    MusicPlayer *musicPlayer;

};

#endif // MAINWINDOW_H
