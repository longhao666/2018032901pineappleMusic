#include "mylistwidget.h"

#include <QAction>
#include <QMenu>

MyListWidget::MyListWidget(QWidget *parent) :
    QListWidget(parent)
{
    createAction();
    createMenu();
    createContextMenu();
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenuSlot(QPoint)));

}

MyListWidget::~MyListWidget()
{

}

void MyListWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
#if 0
    qDebug() << event->button();
    qDebug() << event->x() << event->y();
    qDebug() << this->currentRow();
    qDebug() << this->count();
    qDebug() << this->pos();
#endif
}

void MyListWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
#if 0
    this->indexAt();
    emit signalDoubleClicked();
#endif
}

void MyListWidget::contextMenuSlot(QPoint p)
{
    this->m_point = p;
    m_menu->exec(this->mapToGlobal(p));
}

void MyListWidget::createAction()
{
    m_deleteItem = new QAction(tr("删除"), this);
    connect(m_deleteItem, SIGNAL(triggered()), this, SLOT(slotDelelteItem()));
#if 0
    m_exitAction = new QAction("exit",this);
    connect(m_exitAction,SIGNAL(triggered()),this,SLOT(slotQuit()));
//    conn
    m_aboutAction = new QAction("about",this);
    connect(m_aboutAction,SIGNAL(triggered()),this,SLOT(slotAboutQt()));
#endif
}

void MyListWidget::createMenu()
{
    m_menu = new QMenu(this);
    m_menu->setStyleSheet("background-color:white");
    m_menu->addAction(m_deleteItem);
#if 0
    m_menu->addAction(m_exitAction);
    m_menu->addSeparator();
    m_menu->addAction(m_aboutAction);
#endif
}

void MyListWidget::createContextMenu()
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
}

void MyListWidget::slotDelelteItem()
{
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
    emit signaldeleteItem(row);
}
