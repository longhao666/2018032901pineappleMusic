#include "mylistwidget.h"
#include <QDebug>
#include <QMouseEvent>
#include <QAction>
#include <QMenu>

MyListWidget::MyListWidget(QListWidget *parent)
    : QListWidget(parent)
{
#if 1
    createAction();
    createMenu();
    createContextMenu();
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenuSlot(QPoint)));
#endif
#if 0
    QMenu *menu = new QMenu(this);
    QAction *pnew = new QAction("第一项",this);
    QAction *pnew1 = new QAction("第二项",this);
//    connect (pnew,SIGNAL(triggered()),this,SLOT(clickgoose()));
//    connect (pnew1,SIGNAL(triggered()),this,SLOT(clickmms()));
    menu->addAction(pnew);
    menu->addAction(pnew1);
//    menu->move (cursor ().pos ());
    menu->show ();
//    //获得鼠标点击的x，y坐标点
//    int x = pos.x ();
//    int y = pos.y ();
//    QModelIndex index = ui->tableWidget->indexAt (QPoint(x,y));
//    int row = index.row ();//获得QTableWidget列表点击的行数
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
#endif
#if 0
    QAction *m_exitAction1 = new QAction(tr("1231"), this);
    this->addAction(m_exitAction1);
    QAction *m_exitAction2 = new QAction(tr("1232"), this);
    this->addAction(m_exitAction2);
    QAction *m_exitAction3 = new QAction(tr("1233"), this);
    this->addAction(m_exitAction3);
    QAction *m_exitAction4 = new QAction(tr("1234"), this);
    this->addAction(m_exitAction4);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
#endif
#if 0
    Solution 1 :
    给一个 QWidget 添加 QActions，设置
    QWidget 的 contextMenuPolicy 属性为 Qt::ActionsContextMenu 值，使得窗口菜单以这些添加的 QActions 为菜单项组成一个右键菜单。
    1:MyWidget::MyWidget(QWidget *parent)
    2:: QWidget(parent)
    3:{4:setWindowTitle(tr(
    Context Menu Show 1));
        5://为窗口添加QActions
        6:addAction(newQAction(tr(&Open),
    this));
        7:addAction(newQAction(QIcon(
    :/images/mark.png
    ), tr(&Mark),
    this));
        8:addAction(newQAction(tr(&Quit),
    this));
        9://设置contextMenuPolicy属性值为 '以Actions为弹出菜单的菜单项组成菜单'10:setContextMenuPolicy(Qt::ActionsContextMenu);11:}效果：Solution 2 :
    重写 QWidget 的被保护的虚函数
    void QWidget::contextMenuEvent (
    QContextMenuEvent*event)[virtual protected]
    ，设置QWidget 的 contextMenuPolicy 属性为 Qt::DefaultContextMenu 值，其实默认就是这个值，不用显示设置。1:MyWidget::MyWidget(QWidget *parent)2:: QWidget(parent)3:{4:setWindowTitle(tr(
    Context Menu Show 2));5:setContextMenuPolicy(Qt::DefaultContextMenu);
    //其实不用设置，默认就是这个值6:}7:8:9:voidMyWidget::contextMenuEvent(QContextMenuEvent *event)10:{11:QMenu *menu =newQMenu(this);12:menu-addAction(newQAction(tr(&Open
    ), menu));13:menu-addAction(newQAction(QIcon(
    :/images/mark.png
    ), tr(&Mark
    ), menu));14:menu-addAction(newQAction(tr(&Quit
    ), menu));15:menu-move(cursor().pos());

    //让菜单显示的位置在鼠标的坐标上16:menu-show();17:}效果：上面直接是在 contextMenuEvent 函数体里面 new 了个菜单和一些菜单项，这是为了演示。
#endif
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
#if 0
    qDebug() << p << "vvv";

    qDebug() << p.x() << "llll";
    qDebug() << p.y() << "kkkk";
    QModelIndex index = this->indexAt (p);
    int row = index.row ();//获得QTableWidget列表点击的行数
    qDebug() << row;
    qDebug() << this->currentRow();
    qDebug() << this->cursor();
    index = this->indexAt(p);
    qDebug() << this->currentRow();
    qDebug() << row;
//    this->
#endif

}

void MyListWidget::slotQuit()
{
//    qDebug() << this->x() << this->y();
    qDebug() << "void MyListWidget::quit(QPoint p)";
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
//    qDebug() << m_point;
//    qDebug() << row;
//    qDebug() << this->itemAt(m_point)->text() << "item";
    this->takeItem(row);
    emit signaldeleteItem(row);
}

void MyListWidget::slotAboutQt()
{
    qDebug() << "void MyListWidget::aboutQt()";
}

void MyListWidget::slotDelelteItem()
{
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
    emit signaldeleteItem(row);
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
//    this->setContextMenuPolicy(Qt::PreventContextMenu);
}


#if 0
void MyListWidget::show_menu(const QPoint pos)
{
    //设置菜单选项
    QMenu *menu = new QMenu(ui->tableWidget);
    QAction *pnew = new QAction(“第一项”,ui->tableWidget);
    QAction *pnew1 = new QAction(“第二项”,ui->tableWidget);
    connect (pnew,SIGNAL(triggered()),this,SLOT(clickgoose()));
    connect (pnew1,SIGNAL(triggered()),this,SLOT(clickmms()));
    menu->addAction(pnew);
    menu->addAction(pnew1);
    menu->move (cursor ().pos ());
    menu->show ();
    //获得鼠标点击的x，y坐标点
    int x = pos.x ();
    int y = pos.y ();
    QModelIndex index = ui->tableWidget->indexAt (QPoint(x,y));
    int row = index.row ();//获得QTableWidget列表点击的行数
}
#endif

#if 0
QMenu m_menuContext;
TableContentView::TableContentView(QWidget* parent/*=0*/)
    :QTableView(parent)
{
    m_pActNewItem=new QAction(tr("添加记录(&N)"),this);
    m_pActNewItem->setStatusTip(tr("插入一条新纪录"));
    m_menuContext.addAction(m_pActNewItem);
    connect(m_pActNewItem,SIGNAL(triggered()),this,SIGNAL(sigNewItem()));
    m_pActDelItem=new QAction(tr("删除记录(&D)"),this);
    m_pActDelItem->setStatusTip(tr("删除当前选定记录"));
    m_menuContext.addAction(m_pActDelItem);
    connect(m_pActDelItem,SIGNAL(triggered()),this,SIGNAL(sigDelItem()));
    m_menuContext.addSeparator();
    m_pActNewItemBatch=new QAction(tr("批量添加(&B)"),this);
    m_pActNewItemBatch->setStatusTip(tr("一次添加设定数目的记录"));
    m_menuContext.addAction(m_pActNewItemBatch);
    connect(m_pActNewItemBatch,SIGNAL(triggered()),this,SLOT(addItemBatch()));
    m_pActNewItemPaste=new QAction(tr("多列粘贴(&P)"),this);
    m_pActNewItemPaste->setStatusTip(tr("从系统剪切板粘贴多列文本到名称列"));
    m_menuContext.addAction(m_pActNewItemPaste);
    connect(m_pActNewItemPaste,SIGNAL(triggered()),this,SIGNAL(sigItemPaste()));
    m_pActNewItemIns=new QAction(tr("依次加一(&Y)"),this);
    m_pActNewItemIns->setStatusTip(tr("从当前列依次向下加一"));
    m_menuContext.addAction(m_pActNewItemIns);
    connect(m_pActNewItemIns,SIGNAL(triggered()),this,SIGNAL(sigItemIns()));
}
#endif
