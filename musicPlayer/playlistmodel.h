#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractItemModel>
#include <QPoint>

QT_BEGIN_NAMESPACE
class QMediaPlaylist;
QT_END_NAMESPACE

class QAction;
class QMenu;

class PlaylistModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Column
    {
        Title = 0,
        ColumnCount
    };

    PlaylistModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QMediaPlaylist *playlist() const;
    void setPlaylist(QMediaPlaylist *playlist);
    //Qt::DisplayRole   0   The key data to be rendered in the form of text. (QString)
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole) override;

private slots:
    void beginInsertItems(int start, int end);
    void endInsertItems();
    void beginRemoveItems(int start, int end);
    void endRemoveItems();
    void changeItems(int start, int end);

private:
    QMediaPlaylist *m_playlist;
    QMap<QModelIndex, QVariant> m_data;

#if 0
signals:
    void signaldeleteItem(int row);
    void signalNameUp(int row);
    void signalNameDown(int row);
    void signalListUpdate();
    void signalOpenMusicFile();
    void signalMusicList();

private slots:
    void contextMenuSlot(QPoint p);
    void slotDelelteItem();
    void slotNameUp();
    void slotNameDown();
    void slotListUpdate();
    void slotOpenMusicFile();
    void slotMusicList();

private:
    void createAction();
    void createMenu();
    void createContextMenu();


private:
    QMenu *m_menu;
    QPoint m_point;
    QAction *m_deleteItem;
    QAction *m_nameUp;
    QAction *m_nameDown;
    QAction *m_listUpdate;
    QAction *m_openMusicFile;
    QAction *m_musicList;
#endif
};

#endif // PLAYLISTMODEL_H
