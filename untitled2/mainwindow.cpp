#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->setMovable(false);

    QMetaObject::Connection a1 = connect(ui->listWidget, &MyListWidget::doubleClicked, this, &MainWindow::slotDoubleClicked);
    connect(ui->listWidget, &MyListWidget::clicked, this, &MainWindow::slotClicked);
    QMetaObject::Connection a2 = connect(ui->listWidget, &MyListWidget::signaldeleteItem, this, &MainWindow::slotDeleteItem);
    qDebug() << a1;
    qDebug() << a2;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotDoubleClicked(const QModelIndex &index)
{
    qDebug() << "jin le ma";
}

void MainWindow::slotClicked(const QModelIndex &index)
{
    qDebug() << " hh le ma";
}

void MainWindow::slotDeleteItem(int row)
{
    qDebug() << "lll";
    ui->listWidget->takeItem(row);
}
