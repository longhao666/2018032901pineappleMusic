#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>
#include <QProcess>
#include <QMap>
#include <QDir>
#include <QListWidgetItem>
#include <QSound>
#include <QTimer>
#include <QStringList>
#include <QFile>

struct SongInfo
{
    QString fileName;
    QString artist;
    float curTime;
    float songLen;
    int percent;
    QString album;
};

namespace Ui {
    class Music;
}

class Music : public QWidget
{
    Q_OBJECT

public:
    explicit Music(QWidget *parent = 0);
    ~Music();

    void initPlay();//播放音乐
    //QSound *sound_play;
    void showMessage();//显示歌曲相关信息
    void showIrc();
    QStringList readFile(QString fileName);
    int readLrcFile(QString );

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButtonVolumn_clicked();
    void on_horizontalSliderVolumn_valueChanged(int value);
    void on_pushButton_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_5_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void doTimeOut();//发送命令以获得信息
    void getMessage();//获取歌曲相关信息
    void pressListPlay(QListWidgetItem*);
    void pressList(int);

private slots:
    void on_pushButton_4_clicked();
    void on_pushButtonStart_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Music *ui;

    QProcess *process;//进程
    QString musicPath;//音乐路径
    QString ircPath;
    QDir Dir;
    QDir dirLrc;
    void getFile(QDir &);//获取歌曲路径
    QListWidgetItem *item;//歌曲列表

    QMap<int,QListWidgetItem *> songMap;//歌曲名字
    //QMap<int,QListWidgetItem *> songMap2;//歌曲名字
    QMap<float,QString> lrcMap;//歌词

    int currentFlag;//播放当前歌曲
    int backNum;
    int volumvFlag;

    QTimer *timer;
    struct SongInfo songInfo;//存储歌曲相关信息

    float lastTime;
};

#endif // MUSIC_H
