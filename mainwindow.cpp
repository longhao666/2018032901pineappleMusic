#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainToolBar->setMovable(false);

    p1 = new QPushButton(tr("退出"), this);
    ui->mainToolBar->addWidget(p1);
    connect(p1, &QPushButton::clicked, this, slotEnterWidget);

    player = new Player(ui->centralWidget);
    player->setGeometry(0, 0, this->width(), this->height()-50);
    player->player->setVolume(20);

    databaseDriver = new DatabaseDriver();
//    databaseDriver = new DatabaseDriver(ui->centralWidget);
//    databaseDriver->move((this->width() - databaseDriver->width())/2, (this->height() - databaseDriver->height())/2);
    connect(databaseDriver, &DatabaseDriver::signalEnterClicked, this, &MainWindow::slotPlayerShow);
    connect(databaseDriver, &DatabaseDriver::signalQuitClicked, this, &MainWindow::slotWidgetClost);

    this->slotEnterWidget();
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow::~MainWindow()";
    delete ui;
    delete databaseDriver;
//    delete player;
}

void MainWindow::slotEnterWidget()
{
    p1->setEnabled(false);
//    player->hide();
    this->hide();
    databaseDriver->show();
}

void MainWindow::slotMusicWidget()
{

}

void MainWindow::slotPlayerShow()
{
    p1->setEnabled(true);
    this->show();
//    player->show();
}

void MainWindow::slotWidgetClost()
{
//    this->close();
    databaseDriver->close();
}
