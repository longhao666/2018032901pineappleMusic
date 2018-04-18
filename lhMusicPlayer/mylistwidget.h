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
    void signalOpenMusicFile();

private slots:
    void contextMenuSlot(QPoint p);
    void slotDelelteItem();
    void slotNameUp();
    void slotNameDown();
    void slotListUpdate();
    void slotOpenMusicFile();

private:
    void createAction();
    void createMenu();
    void createContextMenu();


private:
    QMenu* m_menu;
    QPoint m_point;
    QAction *m_deleteItem;
    QAction *m_nameUp;
    QAction *m_nameDown;
    QAction *m_listUpdate;
    QAction *m_openMusicFile;
};

#endif // MYLISTWIDGET_H
