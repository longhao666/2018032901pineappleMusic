#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>


class SongLyric;
class QSqlQuery;

namespace Ui {
class MusicPlayer;
}

class Q_DECL_EXPORT MusicPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayer(QWidget *parent = 0);
    ~MusicPlayer();

public slots:



protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void slotOpenClicked();
    void slotStopClicked();
    void slotPreClicked();
    void slotPauseClicked();
    void slotNextClicked();
    void slotMuteClicked();
    void slotSpeedClicked(QString str);
    void slotSkinClicked();
    void slotDoubleSongClick(const QModelIndex &index);
    void slotMusicPositionChange(qint64 position);
    void slotMusicDurationChange(qint64 duration);
    void slotVolumeChange(int position);
    void slotTimeChange(int position);
    void slotDeleteItem(int row);
    void slotNameUp(int row);
    void slotNameDown(int row);
    void slotListUpdate();
    void slotSkinIndexChange(int index);
    void slotDiscussClicked();
    void slotSearchClicked();

private:
    void updateDurationInfo(qint64 currentInfo);
    void displaySongLyric(int time);
    void getFilePath();
    void showLyric();
    void painterImage();
    void painterImageIndividuationPath();
    void getFilePathList(QString str);



private:
    Ui::MusicPlayer *ui;
    QMediaPlayer *player;
    QStringList *songStringList;
    QStringList *songStringListPath;
    QStringList songStringList1;
    QStringList songStringListPath1;
    int m_playCount;
    int musicTime;
    int backNum;
    SongLyric *lrc;
    QMediaPlayer::State musicState;
    bool isIndividuation;
    QString individuationPath;
    QSqlQuery *query;
};

#endif // MUSICPLAYER_H
