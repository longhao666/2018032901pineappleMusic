#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>


class SongList;

namespace Ui {
class MusicPlayer;
}

class Q_DECL_EXPORT MusicPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayer(QWidget *parent = 0);
    ~MusicPlayer();

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

private:
    void updateDurationInfo(qint64 currentInfo);



private:
    Ui::MusicPlayer *ui;
    QMediaPlayer *player;
    SongList *songList;
    QStringList *songStringList;
    QStringList *songStringListPath;
    int m_playCount;
    int musicTime;
    int backNum;
};

#endif // MUSICPLAYER_H
