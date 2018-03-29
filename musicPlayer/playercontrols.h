#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QMediaPlayer>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QAbstractSlider;
class QComboBox;
QT_END_NAMESPACE

class PlayerControls : public QWidget
{
    Q_OBJECT

public:
    PlayerControls(QWidget *parent = 0);

    QMediaPlayer::State state() const;
    int volume() const;
    bool isMuted() const;
    qreal playbackRate() const;

public slots:
    void setState(QMediaPlayer::State state);
    void setVolume(int volume);
    void setMuted(bool muted);
    void setPlaybackRate(float rate);

signals:
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    void changeVolume(int volume);
    void changeMuting(bool muting);
    void changeRate(qreal rate);

private slots:
    void playClicked();
    void muteClicked();
    void updateRate();
    void onVolumeSliderValueChanged();

private:
    QMediaPlayer::State playerState; //播放状态
    bool playerMuted; //静音状态
    QAbstractButton *playButton; //开始/暂停
    QAbstractButton *stopButton; //停止/退出
    QAbstractButton *nextButton; //下一首
    QAbstractButton *previousButton; //上一首
    QAbstractButton *muteButton; //静音
    QAbstractSlider *volumeSlider; //音量
    QComboBox *rateBox; //播放速度
};

#endif // PLAYERCONTROLS_H
