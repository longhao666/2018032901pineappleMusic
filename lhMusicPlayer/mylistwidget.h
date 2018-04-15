#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include <QWidget>

class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    MyListWidget(QWidget *parent = 0);
    ~MyListWidget();


signals:
    void signaldeleteItem(int row);
    void signalNameUp(int row);
    void signalNameDown(int row);
    void signalListUpdate();

private slots:
    void contextMenuSlot(QPoint p);
    void slotDelelteItem();
    void slotNameUp();
    void slotNameDown();
    void slotListUpdate();

private:
    void createAction();
    void createMenu();
    void createContextMenu();


private:
    QMenu* m_menu;
    QAction* m_exitAction;
    QAction* m_aboutAction;
    QPoint m_point;
    QAction *m_deleteItem;
    QAction *m_nameUp;
    QAction *m_nameDown;
    QAction *m_listUpdate;
};

#endif // MYLISTWIDGET_H
