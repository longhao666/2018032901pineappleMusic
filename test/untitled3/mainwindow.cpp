#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->setMovable(false);

    connect(ui->listWidget, &MyListWidget::doubleClicked, this, &MainWindow::slot1);
    connect(ui->listWidget, &MyListWidget::signaldeleteItem, this, &MainWindow::slot2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot1()
{
    qDebug() << "slot1";
}

void MainWindow::slot2(int row)
{
    qDebug() << "slot1";
    ui->listWidget->takeItem(row);
}
