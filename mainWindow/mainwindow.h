#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasedriver.h"
#include "player.h"
#include "myRecorderWidget.h"


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
    void slotQuitAction();
    void slotKGeAction();

private:
    Ui::MainWindow *ui;
    DatabaseDriver *databaseDriver;
    Player *player;
    QPushButton *p1;
    QPushButton *p2;
    QLabel *l1;
    MusicPlayer *musicPlayer;
    MyRecorderWidget *recorder;


};

#endif // MAINWINDOW_H
