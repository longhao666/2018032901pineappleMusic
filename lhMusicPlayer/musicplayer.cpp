#include "musicplayer.h"
#include "ui_musicplayer.h"
#include <QFileDialog>
#include <QDebug>
#include <QUrl>
#include <QTime>
#include <QPainter>

MusicPlayer::MusicPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("this is Music"));

    player = new QMediaPlayer(this);

    songStringList = new QStringList;
    songStringListPath = new QStringList;
    m_playCount = 0;
    backNum = 0;

    connect(ui->openpushButton, &QPushButton::clicked, this, &MusicPlayer::slotOpenClicked);
    connect(ui->stoppushButton, &QPushButton::clicked, this, &MusicPlayer::slotStopClicked);
    connect(ui->prepushButton, &QPushButton::clicked, this, &MusicPlayer::slotPreClicked);
    connect(ui->pausepushButton, &QPushButton::clicked, this, &MusicPlayer::slotPauseClicked);
    connect(ui->nextpushButton, &QPushButton::clicked, this, &MusicPlayer::slotNextClicked);
    connect(ui->mutepushButton, &QPushButton::clicked, this, &MusicPlayer::slotMuteClicked);
    connect(ui->speedcomboBox, &QComboBox::currentTextChanged, this, &MusicPlayer::slotSpeedClicked);
    connect(ui->skinpushButton, &QPushButton::clicked, this, &MusicPlayer::slotSkinClicked);

    connect(ui->listWidget, &QListWidget::doubleClicked, this, &MusicPlayer::slotDoubleSongClick);
    connect(player, &QMediaPlayer::positionChanged, this, &MusicPlayer::slotMusicPositionChange);
    connect(player, &QMediaPlayer::durationChanged, this, &MusicPlayer::slotMusicDurationChange);
    connect(ui->volumehorizontalSlider, &QSlider::sliderMoved, this, &MusicPlayer::slotVolumeChange);
    connect(ui->timehorizontalSlider, &QSlider::sliderMoved, this, &MusicPlayer::slotTimeChange);

    ui->volumehorizontalSlider->setValue(50);
    ui->speedcomboBox->setCurrentIndex(1);
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
//    delete songList;
    delete songStringList;
}

void MusicPlayer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    const char *backGround[10]={
                           "./image/n14.png",
                           "./image/n2.png",
                           "./image/n4.png",
                           //"./image/n12.png",
                           "./image/b8.png",
                           //"./image/n10.png",
                           "./image/n9.png",
                           "./image/n3.png",
                           "./image/n1.png",
                           "./image/n8.png",
                           "./image/n5.png",
                           //"./image/n11.png",
                           "./image/n15.png"
    };
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(0,0,this->width(),this->height(),
                       QPixmap(backGround[this->backNum]));
}

void pathToSong(const QStringList &s1, QStringList &s2) {
    QString str;
    int count = 0;
    for(int i=0; i<s1.size(); i++) {
        str = s1[i];
        count = str.toStdString().find_last_of("/");
        QString m((str.toStdString().c_str()) + count + 1);
        s2.push_back(m);
    }
}

void MusicPlayer::slotOpenClicked()
{
    ui->listWidget->clear();
#if 0
    QStringList str = QFileDialog::getOpenFileNames(this,
                                                    tr("open Music"),
                                                    tr("./"),
                                                    tr("*.mp3"));
    if(str == NULL) {
        return ;
    }
    for(int i=0;i<str.size();i++) {
        QString s = str.at(i);
        songStringListPath->push_back(s);
    }
    pathToSong(*songStringListPath, *songStringList);
    ui->listWidget->addItems(*songStringList);
#endif
#if 1
    QString str = QFileDialog::getOpenFileName(this,
                                                    tr("open Music"),
                                                    tr(""),
                                                    tr("*.mp3"));
    if(str == NULL) {
        qDebug() << "str is NULL";
        return ;
    }
    songStringListPath->push_back(str);
    int count = str.toStdString().find_last_of("/");
    QString m((str.toStdString().c_str()) + count + 1);
    for(int i=0; i<songStringList->size(); i++) {
        if(songStringList->at(i) == m) {
            qDebug() << "equal";
            songStringList->removeAt(i);
        }
    }
    songStringList->push_back(m);
    ui->listWidget->addItems(*songStringList);
#endif
}

void MusicPlayer::slotStopClicked()
{
    player->stop();
    ui->pausepushButton->setText(tr("播放"));
}

void MusicPlayer::slotPreClicked()
{
    player->stop();
    m_playCount--;
    if(m_playCount == -1) {
        m_playCount = songStringList->length() - 1;
    }
    player->setMedia(QUrl(songStringListPath->at(m_playCount)));
    player->play();
    ui->pausepushButton->setText(tr("暂停"));
}

void MusicPlayer::slotPauseClicked()
{
    if(ui->pausepushButton->text() == "播放") {
        player->play();
        ui->pausepushButton->setText(tr("暂停"));
    }else {
        player->pause();
        ui->pausepushButton->setText(tr("播放"));
    }
    qDebug() << player->duration();
}

void MusicPlayer::slotNextClicked()
{
    player->stop();
    m_playCount++;
    if(m_playCount == songStringList->length()) {
        m_playCount = 0;
    }
    player->setMedia(QUrl(songStringListPath->at(m_playCount)));
    player->play();
    ui->pausepushButton->setText(tr("暂停"));
}

void MusicPlayer::slotMuteClicked()
{
    static int a = 0;
    if(a == 0) {
        a++;
        player->setMuted(true);
    } else {
        a--;
        player->setMuted(false);
    }
}

void MusicPlayer::slotSpeedClicked(QString str)
{
    player->setPlaybackRate(str.toDouble());
}

void MusicPlayer::slotSkinClicked()
{
    this->backNum ++;
    if(this->backNum == 10) {
        this->backNum = 0;
    }
    this->update();
}

void MusicPlayer::slotDoubleSongClick(const QModelIndex &index)
{
    player->stop();
    m_playCount = index.row();
    player->setMedia(QUrl(songStringListPath->at(m_playCount)));
    player->play();
    ui->pausepushButton->setText(tr("暂停"));
}

void MusicPlayer::slotMusicPositionChange(qint64 position)
{
    if (!ui->timehorizontalSlider->isSliderDown()) {
        ui->timehorizontalSlider->setValue(position / 1000);
    }
    updateDurationInfo(position / 1000);
}

void MusicPlayer::slotMusicDurationChange(qint64 duration)
{
    musicTime = duration/1000;
    ui->timehorizontalSlider->setMaximum(duration/1000);
}

void MusicPlayer::slotVolumeChange(int position)
{
    player->setVolume(position);
//    qDebug() << position;
}

void MusicPlayer::slotTimeChange(int position)
{
//    qDebug() << position;
    player->setPosition(position*1000);
}

void MusicPlayer::updateDurationInfo(qint64 currentInfo)
{
    QString tStr;
    if (currentInfo || musicTime) {
        QTime currentTime((currentInfo/3600)%60, (currentInfo/60)%60, currentInfo%60, (currentInfo*1000)%1000);
        QTime totalTime((musicTime/3600)%60, (musicTime/60)%60, musicTime%60, (musicTime*1000)%1000);
        QString format = "mm:ss";
        if (musicTime > 3600) {
            format = "hh:mm:ss";
        }
        // 前面是当前时间,后面是总时间
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    ui->timelabel->setText(tStr);
    if(ui->timehorizontalSlider->value() == musicTime-1) {
//        qDebug() << ui->timehorizontalSlider->value() << musicTime;
        slotNextClicked();
    }
}


