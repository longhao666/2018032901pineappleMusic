#include "musicplayer.h"
#include "ui_musicplayer.h"
#include <QFileDialog>
#include <QDebug>
#include <QUrl>
#include <QTime>
#include <QPainter>
#include <map>


#include "lyricfile.h"

int m_lrcCount = 4;

#if 0
#define MUTEFALSE   "border-image:url(./image/mute_1.png)"
#define MUTETRUE    "border-image:url(./image/mute_0.png)"
#elif 1
#define MUTEFALSE   "border-image:url(./image/sond7.png)"
#define MUTETRUE    "border-image:url(./image/sound.png)"
#endif
#define NEXTIMAGE   "border-image:url(./image/next.png)"
#define PREIMAGE    "border-image:url(./image/previous.png)"
#define PLAYIMAGE   "border-image:url(./image/play.png)"
#define PAUSEIMAGE  "border-image:url(./image/pause.png)"
#define STOPIMAGE   "border-image:url(./image/stop.png)"
#define HOMEIMAGE   "border-image:url(./image/begin.png)"

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
    lrc = new SongLyric;
    musicState = QMediaPlayer::StoppedState;

    connect(ui->openpushButton, &QPushButton::clicked, this, &MusicPlayer::slotOpenClicked);
    connect(ui->stoppushButton, &QPushButton::clicked, this, &MusicPlayer::slotStopClicked);
    connect(ui->prepushButton, &QPushButton::clicked, this, &MusicPlayer::slotPreClicked);
    connect(ui->pausepushButton, &QPushButton::clicked, this, &MusicPlayer::slotPauseClicked);
    connect(ui->nextpushButton, &QPushButton::clicked, this, &MusicPlayer::slotNextClicked);
    connect(ui->mutepushButton, &QPushButton::clicked, this, &MusicPlayer::slotMuteClicked);
    connect(ui->speedcomboBox, &QComboBox::currentTextChanged, this, &MusicPlayer::slotSpeedClicked);
    connect(ui->skinpushButton, &QPushButton::clicked, this, &MusicPlayer::slotSkinClicked);
#if 0
    connect(ui->listWidget, &QListWidget::doubleClicked, this, &MusicPlayer::slotDoubleSongClick);
#elif 1
    connect(ui->listWidget, &MyListWidget::doubleClicked, this, &MusicPlayer::slotDoubleSongClick);
    connect(ui->listWidget, &MyListWidget::signaldeleteItem, this, &MusicPlayer::slotDeleteItem);
    connect(ui->listWidget, &MyListWidget::signalNameUp, this, &MusicPlayer::slotNameUp);
    connect(ui->listWidget, &MyListWidget::signalNameDown, this, &MusicPlayer::slotNameDown);
    connect(ui->listWidget, &MyListWidget::signalListUpdate, this, &MusicPlayer::slotListUpdate);
#endif
    connect(player, &QMediaPlayer::positionChanged, this, &MusicPlayer::slotMusicPositionChange);
    connect(player, &QMediaPlayer::durationChanged, this, &MusicPlayer::slotMusicDurationChange);

    connect(ui->volumehorizontalSlider, &QSlider::sliderMoved, this, &MusicPlayer::slotVolumeChange);
    connect(ui->timehorizontalSlider, &QSlider::sliderMoved, this, &MusicPlayer::slotTimeChange);

    ui->volumehorizontalSlider->setValue(50);
    ui->speedcomboBox->setCurrentIndex(1);

    ui->mutepushButton->setStyleSheet(MUTEFALSE);
    ui->prepushButton->setStyleSheet(PREIMAGE);
    ui->stoppushButton->setStyleSheet(STOPIMAGE);
    ui->nextpushButton->setStyleSheet(NEXTIMAGE);
    ui->pausepushButton->setStyleSheet(PLAYIMAGE);
    ui->skinpushButton->setStyleSheet(HOMEIMAGE);

    this->getFilePath();
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
    delete songStringList;
    delete songStringListPath;
    delete lrc;
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
    ui->listWidget->clear();
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
    musicState = QMediaPlayer::StoppedState;
    ui->pausepushButton->setStyleSheet(PLAYIMAGE);
    m_lrcCount = 4;

}

void MusicPlayer::slotPreClicked()
{
    if(player->mediaStatus() == QMediaPlayer::NoMedia) {
        return ;
    }
    player->stop();
    m_playCount--;
    if(m_playCount <= -1) {
        m_playCount = songStringList->length() - 1;
    }
    player->play();
    ui->pausepushButton->setStyleSheet(PAUSEIMAGE);
    m_lrcCount = 4;
#if 0
    QString str1 = songStringListPath->at(m_playCount);
    QString str2 = str1.left(str1.length() - 4) + QString(".lrc");
    if(! lrc->getLyric(str2.toStdString().c_str())) {
        lrc->lrc.clear();
        ui->textBrowser->setText(tr("没有搜索到歌词"));
    }else {
        ui->textBrowser->setText(tr("歌词搜索中..."));
    }
#endif
#if 0
    QString str1 = songStringList->at(m_playCount);
    QString str2 = str1.right(4);
    lrc->getLyric(str2.toStdString().c_str());
#endif
}

void MusicPlayer::slotPauseClicked()
{
    if(player->mediaStatus() == QMediaPlayer::NoMedia) {
        return ;
    }
    switch (musicState) {
    case QMediaPlayer::PlayingState:
        player->pause();
        musicState = QMediaPlayer::PausedState;
        ui->pausepushButton->setStyleSheet(PLAYIMAGE);
        break;
    case QMediaPlayer::PausedState:
        player->play();
        musicState = QMediaPlayer::PlayingState;
        ui->pausepushButton->setStyleSheet(PAUSEIMAGE);
        break;
    case QMediaPlayer::StoppedState: {
        player->setMedia(QUrl(songStringListPath->at(m_playCount)));
        player->play();
        musicState = QMediaPlayer::PlayingState;
        ui->pausepushButton->setStyleSheet(PAUSEIMAGE);
#if 0
        QString str1 = songStringListPath->at(m_playCount);
        QString str2 = str1.left(str1.length() - 4) + QString(".lrc");
        if(! lrc->getLyric(str2.toStdString().c_str())) {
            lrc->lrc.clear();
            ui->textBrowser->setText(tr("没有搜索到歌词"));
        }else {
            ui->textBrowser->setText(tr("歌词搜索中..."));
        }
#endif
        break;
    }
    default:
        break;
    }
#if 0
    if(ui->pausepushButton->text() == "播放") {
        player->play();
        ui->pausepushButton->setText(tr("暂停"));
    }else {
        player->pause();
        ui->pausepushButton->setText(tr("播放"));
    }
    qDebug() << player->duration();
#endif
#if 0
    QString str1 = songStringList->at(m_playCount);
    QString str2 = str1.right(4);
    lrc->getLyric(str2.toStdString().c_str());
#endif
}

void MusicPlayer::slotNextClicked()
{
    if(player->mediaStatus() == QMediaPlayer::NoMedia) {
        return ;
    }
    player->stop();
    m_playCount++;
    if(m_playCount >= songStringList->length()) {
        m_playCount = 0;
    }
    player->setMedia(QUrl(songStringListPath->at(m_playCount)));
    player->play();
    ui->pausepushButton->setStyleSheet(PAUSEIMAGE);
    m_lrcCount = 4;
#if 0
    QString str1 = songStringListPath->at(m_playCount);
    QString str2 = str1.left(str1.length() - 4) + QString(".lrc");
    if(! lrc->getLyric(str2.toStdString().c_str())) {
        lrc->lrc.clear();
        ui->textBrowser->setText(tr("没有搜索到歌词"));
    }else {
        ui->textBrowser->setText(tr("歌词搜索中..."));
    }
#endif
}

void MusicPlayer::slotMuteClicked()
{
    if(player->mediaStatus() == QMediaPlayer::NoMedia) {
        return ;
    }
    if(player->isMuted()) {
        ui->mutepushButton->setStyleSheet(MUTEFALSE);
        player->setMuted(false);
    }else {
        ui->mutepushButton->setStyleSheet(MUTETRUE);
        player->setMuted(true);
    }
#if 0
    static int a = 0;
    if(a == 0) {
        a++;
        player->setMuted(true);
    } else {
        a--;
        player->setMuted(false);
    }
#endif
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
//    qDebug() << this->x() << this->y() << "you le ? ";
//    qDebug() << "kkkkkkkkkkkkkkk" << ui->listWidget->x() << ui->listWidget->y() ;
//    if(player->mediaStatus() == QMediaPlayer::NoMedia) {
//        return ;
//    }
    qDebug() << "jin le ma";
    player->stop();
    m_playCount = index.row();
    player->setMedia(QUrl(songStringListPath->at(m_playCount)));
    player->play();
    ui->pausepushButton->setStyleSheet(PAUSEIMAGE);
    musicState = QMediaPlayer::PlayingState;
    m_lrcCount = 4;
#if 0
    QString str1 = songStringListPath->at(m_playCount);
    QString str2 = str1.left(str1.length() - 4) + QString(".lrc");
    if(! lrc->getLyric(str2.toStdString().c_str())) {
        lrc->lrc.clear();
        ui->textBrowser->setText(tr("没有搜索到歌词"));
    }else {
        ui->textBrowser->setText(tr("歌词搜索中..."));
    }
#endif
}


void MusicPlayer::slotMusicPositionChange(qint64 position)
{
    if (!ui->timehorizontalSlider->isSliderDown()) {
        ui->timehorizontalSlider->setValue(position / 1000);
    }
    updateDurationInfo(position / 1000);
    displaySongLyric(position / 1000);
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

void MusicPlayer::slotDeleteItem(int row)
{
    if(row == -1) {
        return ;
    }
    ui->listWidget->takeItem(row);
    songStringList->removeAt(row);
    songStringListPath->removeAt(row);
}

void MusicPlayer::slotNameUp(int row)
{
    qDebug() << "void MusicPlayer::slotNameUp(int row)" << row;
    if(row == -1) {
        return ;
    }
}

void MusicPlayer::slotNameDown(int row)
{
    qDebug() << "void MusicPlayer::slotNameDown(int row)" << row;
    if(row == -1) {
        return ;
    }
}

void MusicPlayer::slotListUpdate()
{

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
        m_lrcCount = 4;
        lrc->lrc.clear();
    }
}

void MusicPlayer::displaySongLyric(int time)
{
#if 0
    if(lrc->lrc.count(time) == 0) {
        return ;
    }
    if(m_lrcCount == 4) {
        m_lrcCount++;
        QString str1(lrc->lrc[-4].c_str());
        ui->textBrowser->setText(str1);
        QString str2(lrc->lrc[-3].c_str());
        ui->textBrowser->append(str2);
        QString str3(lrc->lrc[-2].c_str());
        ui->textBrowser->append(str3);
        QString str4(lrc->lrc[-1].c_str());
        ui->textBrowser->append(str4);
    }
    QString str(lrc->lrc[time].c_str());
    ui->textBrowser->append(str);
#endif
}


/**
 * @brief Widget::getFilePath
 * 遍历目录下所有文件，并过滤后缀名，最后打印完整的文件路径直接上代码：
 */
void MusicPlayer::getFilePath()
{
    ui->listWidget->clear();
    songStringListPath->clear();
    songStringList->clear();
#if 0
    QString path = "D:/QtProject/QtMusic/lhMusicSong/好歌";
#elif 1
    QString path = "./music";
#endif
    //qDebug("jinle");
    QDir dir(path);
    //判断路径是否存在
    if(!dir.exists()) {
        qDebug("113, dir is NULL");
        return ;
    }

    QStringList filters;
    filters << QString("*.mp3");
    dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
    dir.setNameFilters(filters); //设置文件名称过滤器，只为filters格式（后缀为.jpeg等图片格式）

    int dirCount = dir.count();
    if(dirCount <= 0) {
        return ;
    }
#if 0
    QStringList stringList;
    //获取分隔符
    //QChar separator = QDir::separator();
    QChar separator = QChar('/');
    if(!path.contains(separator)) {
        separator = QChar('\\');
    }
    QChar last_char = path.at(path.length()-1);
    if(last_char == separator) {
        separator = QChar();
    }

    foreach(QFileInfo mfi ,dir.entryInfoList()) {
        if(mfi.isFile()) {
            QString file_path = path + separator +  mfi.fileName();
            stringList.append(file_path);
        }
    }

    for (int i=0; i< stringList.size(); ++i) {
        qDebug() << stringList.at(i);
    }
#endif

    /**
     * 上面的替换成下面这个,添加到歌曲列表中
     */
    //QStringList stringList;
    //获取分隔符
    //QChar separator = QDir::separator();
    QChar separator = QChar('/');
#if 0
    if(!path.contains(separator)) {
        separator = QChar('\\');
    }
    QChar last_char = path.at(path.length()-1);
    if(last_char == separator) {
        separator = QChar();
    }
#endif

    foreach(QFileInfo mfi ,dir.entryInfoList()) {
        if(mfi.isFile()) {
            QString file_path = path + separator +  mfi.fileName();
            songStringListPath->append(file_path);
            // 这里还添加一个歌名列表
            songStringList->append(mfi.fileName());
        }
    }
    ui->listWidget->addItems(*songStringList);
}


