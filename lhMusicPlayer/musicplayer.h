#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>


class SongLyric;

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

private:
    void updateDurationInfo(qint64 currentInfo);
    void displaySongLyric(int time);
    void getFilePath();



private:
    Ui::MusicPlayer *ui;
    QMediaPlayer *player;
    QStringList *songStringList;
    QStringList *songStringListPath;
    int m_playCount;
    int musicTime;
    int backNum;
    SongLyric *lrc;
    QMediaPlayer::State musicState;
};

#endif // MUSICPLAYER_H
