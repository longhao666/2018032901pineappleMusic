#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include <QObject>

class Q_DECL_EXPORT MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    MyListWidget(QListWidget *parent = 0);
    ~MyListWidget();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void signalQuit(QPoint p);
    void signaldeleteItem(int row);
    void signalDoubleClicked(const QModelIndex &index);

private slots:
    void contextMenuSlot(QPoint p);
    void slotQuit();
    void slotAboutQt();
    void slotDelelteItem();

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
};

#endif // MYLISTWIDGET_H
