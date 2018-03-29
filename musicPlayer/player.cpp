/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "player.h"

#include "playercontrols.h"
#include "playlistmodel.h"
#include "histogramwidget.h"

#include <QMediaService>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QAudioProbe>
#include <QMediaMetaData>
#include <QtWidgets>

/**
 * @brief Player::Player
 * @param parent
 * 构造函数
 */
Player::Player(QWidget *parent)
    : QWidget(parent)
    , videoWidget(0)
    , coverLabel(0)
    , slider(0)
    , colorDialog(0)
{
//! [create-objs]

    /**
The QMediaPlayer class allows the playing of a media source.
译文：QMediaPlayer类允许播放媒体源。
The QMediaPlayer class is a high level media playback class.
It can be used to playback such content as songs, movies and internet radio.
The content to playback is specified as a QMediaContent object,
which can be thought of as a main or canonical URL with
additional information attached. When provided with
a QMediaContent playback may be able to commence.
译文：QMediaPlayer类是一个高级的媒体播放类。
它可以用来播放歌曲、电影和网络电台等内容。
播放的内容被指定为一个QMediaContent对象，
哪个可以被认为是一个主要的或规范的URL
附加的额外信息。当提供
一个QMediaContent回放可以开始。
      */
    // 音乐播放器对象申请空间
    player = new QMediaPlayer(this);
    // owned by PlaylistModel
    // 创建
    /**
QMediaPlaylist表面上只是一个媒体播放列表一样，保存了很多的媒体的路径，可是远不知这些。
此类有一个函数，void    setPlaybackMode(PlaybackMode mode)，而
enum    PlaybackMode { CurrentItemOnce, CurrentItemInLoop, Sequential, Loop, Random }
分别为播放一次，单循环，顺序，列表循环，随机播放，这个为我们提供了很大的方便。
The QMediaPlaylist class provides a list of media content to play.
译文：QMediaPlaylist类提供了一个用于播放的媒体内容列表
QMediaPlaylist is intended to be used with other media objects, like QMediaPlayer.
QMediaPlaylist allows to access the service intrinsic playlist functionality if available,
otherwise it provides the local memory playlist implementation.
译文：QMediaPlaylist旨在与其他媒体对象(如QMediaPlayer)一起使用。
QMediaPlaylist允许访问服务的内在播放列表功能，
否则，它提供本地内存播放列表实现。
      */
    // 播放列表对象申请空间
    playlist = new QMediaPlaylist();
    player->setPlaylist(playlist);
//! [create-objs]

    connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(player, SIGNAL(metaDataChanged()), SLOT(metaDataChanged()));
    connect(playlist, SIGNAL(currentIndexChanged(int)), SLOT(playlistPositionChanged(int)));
    //
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(statusChanged(QMediaPlayer::MediaStatus)));
    connect(player, SIGNAL(bufferStatusChanged(int)), this, SLOT(bufferingProgress(int)));
    connect(player, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailableChanged(bool)));
    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(displayErrorMessage()));
    connect(player, &QMediaPlayer::stateChanged, this, &Player::stateChanged);

//! [2]
    // 视频窗口对象申请空间
    videoWidget = new VideoWidget(this);
    player->setVideoOutput(videoWidget);
    // 播放列表模式对象申请空间
    playlistModel = new PlaylistModel(this);
    playlistModel->setPlaylist(playlist);
//! [2]
    // 申请空间
    playlistView = new QListView(this);
    playlistView->setModel(playlistModel);
    playlistView->setCurrentIndex(playlistModel->index(playlist->currentIndex(), 0));

    connect(playlistView, SIGNAL(activated(QModelIndex)), this, SLOT(jump(QModelIndex)));

    // 申请空间
    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, player->duration() / 1000);

    // 申请空间
    labelDuration = new QLabel(this);
    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));

    // 申请空间
    labelHistogram = new QLabel(this);
    labelHistogram->setText("Histogram:");
    // 申请空间
    videoHistogram = new HistogramWidget(this);
    // 申请空间
    audioHistogram = new HistogramWidget(this);

    // 申请布局空间  直方图布局
    QHBoxLayout *histogramLayout = new QHBoxLayout;
    // 标签
    histogramLayout->addWidget(labelHistogram);
    // 视频
    histogramLayout->addWidget(videoHistogram, 1);
    // 音频
    histogramLayout->addWidget(audioHistogram, 2);

    videoProbe = new QVideoProbe(this);
    connect(videoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), videoHistogram, SLOT(processFrame(QVideoFrame)));
    videoProbe->setSource(player);

    audioProbe = new QAudioProbe(this);
    connect(audioProbe, SIGNAL(audioBufferProbed(QAudioBuffer)), audioHistogram, SLOT(processBuffer(QAudioBuffer)));
    audioProbe->setSource(player);

    QPushButton *openButton = new QPushButton(tr("Open"), this);

    connect(openButton, SIGNAL(clicked()), this, SLOT(open()));
    // 创建 自定义的类,有暂停,播放,等功能
    PlayerControls *controls = new PlayerControls(this);
    controls->setState(player->state());
    controls->setVolume(player->volume());
    controls->setMuted(controls->isMuted());

    //! 一系列信号与槽
    // A:
    connect(controls, SIGNAL(play()), player, SLOT(play()));
    connect(controls, SIGNAL(pause()), player, SLOT(pause()));
    connect(controls, SIGNAL(stop()), player, SLOT(stop()));
    connect(controls, SIGNAL(next()), playlist, SLOT(next()));
    connect(controls, SIGNAL(previous()), this, SLOT(previousClicked()));
    connect(controls, SIGNAL(changeVolume(int)), player, SLOT(setVolume(int)));
    connect(controls, SIGNAL(changeMuting(bool)), player, SLOT(setMuted(bool)));
    connect(controls, SIGNAL(changeRate(qreal)), player, SLOT(setPlaybackRate(qreal)));

    connect(controls, SIGNAL(stop()), videoWidget, SLOT(update()));
    // B:
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)),
            controls, SLOT(setState(QMediaPlayer::State)));
    connect(player, SIGNAL(volumeChanged(int)), controls, SLOT(setVolume(int)));
    connect(player, SIGNAL(mutedChanged(bool)), controls, SLOT(setMuted(bool)));

    //! 布局吧
    // 满屏按钮申请空间
    fullScreenButton = new QPushButton(tr("FullScreen"), this);
    fullScreenButton->setCheckable(true);
    // 颜色按钮申请空间
    colorButton = new QPushButton(tr("Color Options..."), this);
    colorButton->setEnabled(false);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(showColorDialog()));
    /**
@函数:
void QBoxLayout::addWidget(QWidget *widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment())

Adds widget to the end of this box layout, with a stretch factor of stretch and alignment alignment.
译文：将小部件添加到此框布局的末尾，并具有拉伸和对齐对齐的拉伸因子。
The stretch factor applies only in the direction of the QBoxLayout, and is relative to the other boxes
and widgets in this QBoxLayout. Widgets and boxes with higher stretch factors grow more.
译文：拉伸因子只适用于QBoxLayout的方向，相对于其他的盒子
以及这个QBoxLayout中的小部件。具有较高拉伸系数的小部件和盒子长得更大。
If the stretch factor is 0 and nothing else in the QBoxLayout has a stretch factor greater than zero,
the space is distributed according to the QWidget:sizePolicy() of each widget that's involved.
译文：如果拉伸因子为0，而QBoxLayout中没有其他元素的拉伸因子大于零，
空间根据QWidget:涉及的每个小部件的sizePolicy()分布。
The alignment is specified by alignment. The default alignment is 0, which means that the widget fills
the entire cell.
译文：对齐是通过对齐来指定的。默认对齐为0，这意味着小部件填充整个单元格。
See also insertWidget(), addItem(), addLayout(), addStretch(), addSpacing(), and addStrut().
译文：参见insertWidget()、addItem()、addLayout()、addStretch()、add间距()和addStrut()。
      */
    // 1.水平布局 展示布局
    QBoxLayout *displayLayout = new QHBoxLayout;
    // 添加窗口
    // 列表  因为先添加进去,所以在左边
    displayLayout->addWidget(playlistView);
    // 视频
    displayLayout->addWidget(videoWidget, 2);

    // 2.水平布局  控制音乐的布局
    QBoxLayout *controlLayout = new QHBoxLayout;
    // 设置边缘
    controlLayout->setMargin(0);
    controlLayout->addWidget(openButton);  // 一个
    // 添加伸展大小
    controlLayout->addStretch(1);
    controlLayout->addWidget(controls); // 两个
    controlLayout->addStretch(1);

    controlLayout->addWidget(fullScreenButton);// 3个
    controlLayout->addWidget(colorButton); // 4个
    // 3.垂直布局  总布局
    QBoxLayout *layout = new QVBoxLayout;
    // 把展示布局添加进去
    layout->addLayout(displayLayout);
    // 4.垂直布局 滑块布局.就是进度条
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(slider);
    hLayout->addWidget(labelDuration);
    // 添加布局
    layout->addLayout(hLayout);
    // 把控制音乐的布局添加进去
    layout->addLayout(controlLayout);
    // 把直方图的布局添加进去
    layout->addLayout(histogramLayout);

    setLayout(layout);

    if (!isPlayerAvailable()) {
        QMessageBox::warning(this, tr("Service not available"),
                             tr("The QMediaPlayer object does not have a valid service.\n"\
                                "Please check the media service plugins are installed."));

        controls->setEnabled(false);
        playlistView->setEnabled(false);
        openButton->setEnabled(false);
        colorButton->setEnabled(false);
        fullScreenButton->setEnabled(false);
    }

    metaDataChanged();
}

Player::~Player()
{
}

bool Player::isPlayerAvailable() const
{
    /**
      Returns true if the service is available for use.
      译文：如果服务可用，返回true。
      */
    return player->isAvailable();
}

/**
 * @brief Player::open
 * 槽函数
 * 由打开按钮点击触发
 */
void Player::open()
{
    //qDebug("jinle open");
    /**
     * @brief fileDialog
The QFileDialog class provides a dialog that allow users to select files or directories.
译文：QFileDialog类提供一个对话框，允许用户选择文件或目录。
The QFileDialog class enables a user to traverse the file system in order to select one
or many files or a directory.
译文：QFileDialog类允许用户遍历文件系统，以选择一个或多个文件或目录。
The easiest way to create a QFileDialog is to use the static functions.
译文：创建QFileDialog的最简单方法是使用静态函数。
     */
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Files"));
//    fileDialog.setDirectory("");
    QStringList supportedMimeTypes = player->supportedMimeTypes();
    qDebug() << "supportedMimeTypes =" << supportedMimeTypes << __func__;
    if (!supportedMimeTypes.isEmpty()) {
        supportedMimeTypes.append("audio/x-m3u"); // MP3 playlists
        fileDialog.setMimeTypeFilters(supportedMimeTypes);
    }
//    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
//    fileDialog.setDirectory("./");
    if (fileDialog.exec() == QDialog::Accepted)
        addToPlaylist(fileDialog.selectedUrls());
    //qDebug("chule open");
}

static bool isPlaylist(const QUrl &url) // Check for ".m3u" playlists.
{
    /**
Returns true if this URL is pointing to a local file path.
A URL is a local file path if the scheme is "file".
Note that this function considers URLs with hostnames to be local file paths,
even if the eventual file path cannot be opened with QFile::open().
This function was introduced in Qt 4.8.
译文：返回true，如果该URL指向一个本地文件路径。如果该方案是“文件”，则URL是本地文件路径。
注意，该函数考虑带有主机名的url是本地文件路径，即使最终文件路径不能用QFile打开::open()。
这个函数是在Qt 4.8中引入的。
      */
    if (!url.isLocalFile())
        return false;
    const QFileInfo fileInfo(url.toLocalFile());
    return fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive);
}

/**
 * @brief Player::addToPlaylist
 * @param urls
 */
void Player::addToPlaylist(const QList<QUrl> urls)
{
    foreach (const QUrl &url, urls) {
        if (isPlaylist(url))
            playlist->load(url);
        else
            playlist->addMedia(url);
    }
}

/**
 * @brief Player::durationChanged
 * @param duration
 * 槽函数
 * 给进度条设置最大上限
 */
void Player::durationChanged(qint64 duration)
{
    /**
This property holds the slider's maximum value
When setting this property, the minimum is adjusted if necessary to ensure that
the range remains valid. Also the slider's current value is adjusted to be within the new range.
译文：此属性保存滑块的最大值
在设置此属性时，如果有必要，将对最小值进行调整，以确保该范围仍然有效。此外，滑动器的当前值也会调整到新的范围内。
Access functions: 访问功能:
int  maximum() const
void setMaximum(int)
      */
    this->duration = duration/1000;
    slider->setMaximum(duration / 1000);
}

/**
 * @brief Player::positionChanged
 * @param progress
 * 槽函数
 * 位置的变化改变进度条的变化
 */
void Player::positionChanged(qint64 progress)
{
    if (!slider->isSliderDown()) {
        slider->setValue(progress / 1000);
    }
    updateDurationInfo(progress / 1000);
}

/**
 * @brief Player::metaDataChanged
 */
void Player::metaDataChanged()
{
    if (player->isMetaDataAvailable()) {
        setTrackInfo(QString("%1 - %2")
                .arg(player->metaData(QMediaMetaData::AlbumArtist).toString())
                .arg(player->metaData(QMediaMetaData::Title).toString()));

        if (coverLabel) {
            QUrl url = player->metaData(QMediaMetaData::CoverArtUrlLarge).value<QUrl>();

            coverLabel->setPixmap(!url.isEmpty()
                    ? QPixmap(url.toString())
                    : QPixmap());
        }
    }
}

void Player::previousClicked()
{
    // Go to previous track if we are within the first 5 seconds of playback
    // Otherwise, seek to the beginning.
    if(player->position() <= 5000)
        /**
Return to the previous media content in playlist.
译文：返回到播放列表中的前一个媒体内容。
          */
        playlist->previous();
    else
        /**
This property holds the playback position of the current media.
The value is the current playback position, expressed in milliseconds since the beginning of the media.
Periodically changes in the position will be indicated with the signal positionChanged(),
the interval between updates can be set with QMediaObject's method setNotifyInterval().
译文：
此属性保存当前媒体的播放位置。
该值是当前播放位置，自媒体开始时以毫秒表示。
位置的周期性变化将用信号positionChanged()表示，
更新的间隔可以设置为QMediaObject的方法setNotifyInterval()。
          */
        player->setPosition(0);
}

/**
 * @brief Player::jump
 * @param index
 * 槽函数
 */
void Player::jump(const QModelIndex &index)
{
    if (index.isValid()) {
        playlist->setCurrentIndex(index.row());
        player->play();
    }
}

void Player::playlistPositionChanged(int currentItem)
{
    clearHistogram();
    playlistView->setCurrentIndex(playlistModel->index(currentItem, 0));
}

void Player::seek(int seconds)
{
    player->setPosition(seconds * 1000);
}

/**
 * @brief Player::statusChanged
 * @param status
 * 槽函数
 * 由媒体的状态调用这个槽
 */
void Player::statusChanged(QMediaPlayer::MediaStatus status)
{
    handleCursor(status);

    // handle status message
    switch (status) {
    case QMediaPlayer::UnknownMediaStatus: // 0
    case QMediaPlayer::NoMedia: // 1
    case QMediaPlayer::LoadedMedia: // 2
    case QMediaPlayer::BufferingMedia: // 3
    case QMediaPlayer::BufferedMedia: // 4
        setStatusInfo(QString());
        break;
    case QMediaPlayer::LoadingMedia: // 5
        setStatusInfo(tr("Loading..."));
        break;
    case QMediaPlayer::StalledMedia: // 6
        setStatusInfo(tr("Media Stalled"));
        break;
    case QMediaPlayer::EndOfMedia: // 7
        QApplication::alert(this);
        break;
    case QMediaPlayer::InvalidMedia: // 8
        displayErrorMessage();
        break;
    default :
        break;
    }
}

/**
 * @brief Player::stateChanged
 * @param state
 * 槽函数
 * 情形改变后调用此槽函数
 */
void Player::stateChanged(QMediaPlayer::State state)
{
    /**

QMediaPlayer::StoppedState 0
The media player is not playing content, playback will begin from the start of the current track.
媒体播放器不播放内容，播放将从当前轨道的开始开始。
QMediaPlayer::PlayingState 1
The media player is currently playing content.
媒体播放器目前正在播放内容。
QMediaPlayer::PausedState 2
The media player has paused playback, playback of the current track will resume from the position the player was paused at.
媒体播放器暂停播放，播放当前曲目将从玩家被暂停的位置恢复。

      */
    if (state == QMediaPlayer::StoppedState)
        clearHistogram();
}

void Player::handleCursor(QMediaPlayer::MediaStatus status)
{
#ifndef QT_NO_CURSOR
    if (status == QMediaPlayer::LoadingMedia ||
        status == QMediaPlayer::BufferingMedia ||
        status == QMediaPlayer::StalledMedia)
        setCursor(QCursor(Qt::BusyCursor));
    else
        unsetCursor();
#endif
}

void Player::bufferingProgress(int progress)
{
    setStatusInfo(tr("Buffering %4%").arg(progress));
}

void Player::videoAvailableChanged(bool available)
{
    if (!available) {
        disconnect(fullScreenButton, SIGNAL(clicked(bool)),
                    videoWidget, SLOT(setFullScreen(bool)));
        disconnect(videoWidget, SIGNAL(fullScreenChanged(bool)),
                fullScreenButton, SLOT(setChecked(bool)));
        videoWidget->setFullScreen(false);
    } else {
        connect(fullScreenButton, SIGNAL(clicked(bool)),
                videoWidget, SLOT(setFullScreen(bool)));
        connect(videoWidget, SIGNAL(fullScreenChanged(bool)),
                fullScreenButton, SLOT(setChecked(bool)));

        if (fullScreenButton->isChecked())
            videoWidget->setFullScreen(true);
    }
    colorButton->setEnabled(available);
}

void Player::setTrackInfo(const QString &info)
{
    trackInfo = info;
    if (!statusInfo.isEmpty())
        setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
    else
        setWindowTitle(trackInfo);
}

void Player::setStatusInfo(const QString &info)
{
    statusInfo = info;
    if (!statusInfo.isEmpty())
        setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
    else
        setWindowTitle(trackInfo);
}

void Player::displayErrorMessage()
{
    setStatusInfo(player->errorString());
}

/**
 * @brief Player::updateDurationInfo
 * @param currentInfo
 * 随着进度条的移动,把时间显示在label标签上
 */
void Player::updateDurationInfo(qint64 currentInfo)
{
    QString tStr;
    if (currentInfo || duration) {
        QTime currentTime((currentInfo/3600)%60, (currentInfo/60)%60, currentInfo%60, (currentInfo*1000)%1000);
        QTime totalTime((duration/3600)%60, (duration/60)%60, duration%60, (duration*1000)%1000);
        QString format = "mm:ss";
        if (duration > 3600)
            format = "hh:mm:ss";
        // 前面是当前时间,后面是总时间
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    labelDuration->setText(tStr);
}

/**
 * @brief Player::showColorDialog
 * 槽函数
 */
void Player::showColorDialog()
{
    if (!colorDialog) {
        QSlider *brightnessSlider = new QSlider(Qt::Horizontal);
        brightnessSlider->setRange(-100, 100);
        brightnessSlider->setValue(videoWidget->brightness());
        connect(brightnessSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setBrightness(int)));
        connect(videoWidget, SIGNAL(brightnessChanged(int)), brightnessSlider, SLOT(setValue(int)));

        QSlider *contrastSlider = new QSlider(Qt::Horizontal);
        contrastSlider->setRange(-100, 100);
        contrastSlider->setValue(videoWidget->contrast());
        connect(contrastSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setContrast(int)));
        connect(videoWidget, SIGNAL(contrastChanged(int)), contrastSlider, SLOT(setValue(int)));

        QSlider *hueSlider = new QSlider(Qt::Horizontal);
        hueSlider->setRange(-100, 100);
        hueSlider->setValue(videoWidget->hue());
        connect(hueSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setHue(int)));
        connect(videoWidget, SIGNAL(hueChanged(int)), hueSlider, SLOT(setValue(int)));

        QSlider *saturationSlider = new QSlider(Qt::Horizontal);
        saturationSlider->setRange(-100, 100);
        saturationSlider->setValue(videoWidget->saturation());
        connect(saturationSlider, SIGNAL(sliderMoved(int)), videoWidget, SLOT(setSaturation(int)));
        connect(videoWidget, SIGNAL(saturationChanged(int)), saturationSlider, SLOT(setValue(int)));

        QFormLayout *layout = new QFormLayout;
        layout->addRow(tr("Brightness"), brightnessSlider);
        layout->addRow(tr("Contrast"), contrastSlider);
        layout->addRow(tr("Hue"), hueSlider);
        layout->addRow(tr("Saturation"), saturationSlider);

        QPushButton *button = new QPushButton(tr("Close"));
        layout->addRow(button);

        colorDialog = new QDialog(this);
        colorDialog->setWindowTitle(tr("Color Options"));
        colorDialog->setLayout(layout);

        connect(button, SIGNAL(clicked()), colorDialog, SLOT(close()));
    }
    colorDialog->show();
}

void Player::clearHistogram()
{
    QMetaObject::invokeMethod(videoHistogram, "processFrame", Qt::QueuedConnection, Q_ARG(QVideoFrame, QVideoFrame()));
    QMetaObject::invokeMethod(audioHistogram, "processBuffer", Qt::QueuedConnection, Q_ARG(QAudioBuffer, QAudioBuffer()));
}
