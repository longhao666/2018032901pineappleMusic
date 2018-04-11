#ifndef PLAYER_H
#define PLAYER_H

#include "videowidget.h"

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QLabel;
class QMediaPlayer;
class QModelIndex;
class QPushButton;
class QSlider;
class QVideoProbe;
class QVideoWidget;
class QAudioProbe;
QT_END_NAMESPACE


class PlaylistModel;
class HistogramWidget;

class Q_DECL_EXPORT Player : public QWidget
{
    Q_OBJECT

public:
    Player(QWidget *parent = 0);
    ~Player();

    bool isPlayerAvailable() const;

    void addToPlaylist(const QList<QUrl> urls);

signals:
    void fullScreenChanged(bool fullScreen);

private slots:
    void open();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);
    void metaDataChanged();

    void previousClicked();

    void seek(int seconds);
    void jump(const QModelIndex &index);
    void playlistPositionChanged(int);

    void statusChanged(QMediaPlayer::MediaStatus status);
    void stateChanged(QMediaPlayer::State state);
    void bufferingProgress(int progress);
    void videoAvailableChanged(bool available);

    void displayErrorMessage();

    void showColorDialog();

private:
    void clearHistogram();
    void setTrackInfo(const QString &info);
    void setStatusInfo(const QString &info);
    void handleCursor(QMediaPlayer::MediaStatus status);
    void updateDurationInfo(qint64 currentInfo);

public:
    QMediaPlayer *player;
private:
    QMediaPlaylist *playlist;
    VideoWidget *videoWidget;
    QLabel *coverLabel;
    // 滑块,快进的
    QSlider *slider;
    QLabel *labelDuration;
    QPushButton *fullScreenButton; // 全屏按钮
    QPushButton *colorButton; // 颜色按钮
    QDialog *colorDialog;

    QLabel *labelHistogram;
    HistogramWidget *videoHistogram;
    HistogramWidget *audioHistogram;
    QVideoProbe *videoProbe;
    QAudioProbe *audioProbe;

    PlaylistModel *playlistModel;
    QAbstractItemView *playlistView;
    QString trackInfo;
    QString statusInfo;
    qint64 duration;
    QStringList *stringList;
};

#endif // PLAYER_H
