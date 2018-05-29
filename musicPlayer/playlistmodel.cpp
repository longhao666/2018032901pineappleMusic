#include "playlistmodel.h"

#include <QFileInfo>
#include <QUrl>
#include <QMediaPlaylist>
#include <QAction>
#include <QMenu>
#include <QModelIndex>

PlaylistModel::PlaylistModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_playlist(0)
{
#if 0
    createAction();
    createMenu();
    createContextMenu();
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenuSlot(QPoint)));
#endif
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
    return m_playlist && !parent.isValid() ? m_playlist->mediaCount() : 0;
}

int PlaylistModel::columnCount(const QModelIndex &parent) const
{
    return !parent.isValid() ? ColumnCount : 0;
}

QModelIndex PlaylistModel::index(int row, int column, const QModelIndex &parent) const
{
    return m_playlist && !parent.isValid()
            && row >= 0 && row < m_playlist->mediaCount()
            && column >= 0 && column < ColumnCount
        ? createIndex(row, column)
        : QModelIndex();
}

QModelIndex PlaylistModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);

    return QModelIndex();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole) {
        QVariant value = m_data[index];
        if (!value.isValid() && index.column() == Title) {
            QUrl location = m_playlist->media(index.row()).canonicalUrl();
            return QFileInfo(location.path()).fileName();
        }

        return value;
    }
    return QVariant();
}

QMediaPlaylist *PlaylistModel::playlist() const
{
    return m_playlist;
}

/**
 * @brief PlaylistModel::setPlaylist
 * @param playlist
 * 把歌单列表传入进来
 */
void PlaylistModel::setPlaylist(QMediaPlaylist *playlist)
{
    if (m_playlist) {
        disconnect(m_playlist, SIGNAL(mediaAboutToBeInserted(int,int)), this, SLOT(beginInsertItems(int,int)));
        disconnect(m_playlist, SIGNAL(mediaInserted(int,int)), this, SLOT(endInsertItems()));
        disconnect(m_playlist, SIGNAL(mediaAboutToBeRemoved(int,int)), this, SLOT(beginRemoveItems(int,int)));
        disconnect(m_playlist, SIGNAL(mediaRemoved(int,int)), this, SLOT(endRemoveItems()));
        disconnect(m_playlist, SIGNAL(mediaChanged(int,int)), this, SLOT(changeItems(int,int)));
    }
    //开启一个模型复位操作
    beginResetModel();
    m_playlist = playlist;

    if (m_playlist) {
        connect(m_playlist, SIGNAL(mediaAboutToBeInserted(int,int)), this, SLOT(beginInsertItems(int,int)));
        connect(m_playlist, SIGNAL(mediaInserted(int,int)), this, SLOT(endInsertItems()));
        connect(m_playlist, SIGNAL(mediaAboutToBeRemoved(int,int)), this, SLOT(beginRemoveItems(int,int)));
        connect(m_playlist, SIGNAL(mediaRemoved(int,int)), this, SLOT(endRemoveItems()));
        connect(m_playlist, SIGNAL(mediaChanged(int,int)), this, SLOT(changeItems(int,int)));
    }
    //完成模型复位操作
    endResetModel();
}

bool PlaylistModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // 显示这个参数在这个函数中不用,可以消除警告
    Q_UNUSED(role);
    m_data[index] = value;
    emit dataChanged(index, index);
    return true;
}

void PlaylistModel::beginInsertItems(int start, int end)
{
    m_data.clear();
    beginInsertRows(QModelIndex(), start, end);
}

void PlaylistModel::endInsertItems()
{
    endInsertRows();
}

void PlaylistModel::beginRemoveItems(int start, int end)
{
    m_data.clear();
    beginRemoveRows(QModelIndex(), start, end);
}

void PlaylistModel::endRemoveItems()
{
    endInsertRows();
}

void PlaylistModel::changeItems(int start, int end)
{
    m_data.clear();
    emit dataChanged(index(start,0), index(end,ColumnCount));
}

#if 0
void PlaylistModel::contextMenuSlot(QPoint p)
{
    this->m_point = p;
    qDebug() << "void MyListWidget::contextMenuSlot(QPoint p)" << p;
    m_menu->exec(this->mapToGlobal(p));
}

void PlaylistModel::slotDelelteItem()
{
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
    qDebug() << "void MyListWidget::slotDelelteItem()" << row;
    emit signaldeleteItem(row);
}

void PlaylistModel::slotNameUp()
{
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
    qDebug() << "void MyListWidget::slotNameUp()" << row;
    emit signalNameUp(row);
}

void PlaylistModel::slotNameDown()
{
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
    qDebug() << "void MyListWidget::slotNameDown()" << row;
    emit signalNameDown(row);
}

void PlaylistModel::slotListUpdate()
{
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
    qDebug() << "void MyListWidget::slotListUpdate()" << row;
    emit signalListUpdate();
}

void PlaylistModel::slotOpenMusicFile()
{
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
    qDebug() << "void MyListWidget::slotOpenMusicFile()" << row;
    emit signalOpenMusicFile();
}

void PlaylistModel::slotMusicList()
{
    QModelIndex index = this->indexAt (m_point);
    int row = index.row ();//获得QTableWidget列表点击的行数
    qDebug() << "void MyListWidget::slotMusicList()" << row;
    emit signalMusicList();
}

void PlaylistModel::createAction()
{
    m_listUpdate = new QAction(tr("刷新"), this);
    connect(m_listUpdate, SIGNAL(triggered()), this, SLOT(slotListUpdate()));
    m_deleteItem = new QAction(tr("删除"), this);
    connect(m_deleteItem, SIGNAL(triggered()), this, SLOT(slotDelelteItem()));
    m_nameUp = new QAction(tr("按名称升序\b"), this);
    connect(m_nameUp, SIGNAL(triggered()), this, SLOT(slotNameUp()));
    m_nameDown = new QAction(tr("按名称降序\b"), this);
    connect(m_nameDown, SIGNAL(triggered()), this, SLOT(slotNameDown()));
    m_openMusicFile = new QAction(tr("添加歌曲"), this);
    connect(m_openMusicFile, SIGNAL(triggered()), this, SLOT(slotOpenMusicFile()));
    m_musicList = new QAction(tr("添加列表"), this);
    connect(m_musicList, SIGNAL(triggered()), this, SLOT(slotMusicList()));
}

void PlaylistModel::createMenu()
{
    m_menu = new QMenu(this);
    m_menu->setStyleSheet("background-color:white");
    m_menu->addAction(m_listUpdate);
    m_menu->addSeparator();
    m_menu->addAction(m_openMusicFile);
    m_menu->addAction(m_musicList);
    m_menu->addSeparator();
    m_menu->addAction(m_deleteItem);
    m_menu->addSeparator();
    m_menu->addAction(m_nameUp);
    m_menu->addAction(m_nameDown);

}

void PlaylistModel::createContextMenu()
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
}
#endif
