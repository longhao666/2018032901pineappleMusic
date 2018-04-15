#include "mylistwidget.h"
#include <QDebug>
#include <QMouseEvent>
#include <QAction>
#include <QMenu>

MyListWidget::MyListWidget(QWidget *parent)
    : QListWidget(parent)
{
    createAction();
    createMenu();
    createContextMenu();
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenuSlot(QPoint)));

}

MyListWidget::~MyListWidget()
{

}



void MyListWidget::contextMenuSlot(QPoint p)
{
    this->m_point = p;
    qDebug() << "void MyListWidget::contextMenuSlot(QPoint p)" << p;
    m_menu->exec(this->mapToGlobal(p));
}

void MyListWidget::slotDelelteItem()
{
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
    qDebug() << "void MyListWidget::slotDelelteItem()" << row;
    emit signaldeleteItem(row);
}

void MyListWidget::slotNameUp()
{
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
    qDebug() << "void MyListWidget::slotNameUp()" << row;
    emit signalNameUp(row);
}

void MyListWidget::slotNameDown()
{
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
    qDebug() << "void MyListWidget::slotNameDown()" << row;
    emit signalNameDown(row);
}

void MyListWidget::slotListUpdate()
{
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
    qDebug() << "void MyListWidget::slotListUpdate()" << row;
    emit signalListUpdate();
}

void MyListWidget::createAction()
{
    m_listUpdate = new QAction(tr("刷新"), this);
    connect(m_listUpdate, SIGNAL(triggered()), this, SLOT(slotListUpdate()));
    m_deleteItem = new QAction(tr("删除"), this);
    connect(m_deleteItem, SIGNAL(triggered()), this, SLOT(slotDelelteItem()));
    m_nameUp = new QAction(tr("按名称升序"), this);
    connect(m_nameUp, SIGNAL(triggered()), this, SLOT(slotNameUp()));
    m_nameDown = new QAction(tr("按名称降序"), this);
    connect(m_nameDown, SIGNAL(triggered()), this, SLOT(slotNameDown()));
}

void MyListWidget::createMenu()
{
    m_menu = new QMenu(this);
    m_menu->setStyleSheet("background-color:white");
    m_menu->addAction(m_listUpdate);
    m_menu->addSeparator();
    m_menu->addAction(m_deleteItem);
    m_menu->addSeparator();
    m_menu->addAction(m_nameUp);
    m_menu->addAction(m_nameDown);

}

void MyListWidget::createContextMenu()
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
}


