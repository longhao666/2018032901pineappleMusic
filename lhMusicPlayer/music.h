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

    void initPlay();//��������
    //QSound *sound_play;
    void showMessage();//��ʾ���������Ϣ
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
    void doTimeOut();//���������Ի����Ϣ
    void getMessage();//��ȡ���������Ϣ
    void pressListPlay(QListWidgetItem*);
    void pressList(int);

private slots:
    void on_pushButton_4_clicked();
    void on_pushButtonStart_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Music *ui;

    QProcess *process;//����
    QString musicPath;//����·��
    QString ircPath;
    QDir Dir;
    QDir dirLrc;
    void getFile(QDir &);//��ȡ����·��
    QListWidgetItem *item;//�����б�

    QMap<int,QListWidgetItem *> songMap;//��������
    //QMap<int,QListWidgetItem *> songMap2;//��������
    QMap<float,QString> lrcMap;//���

    int currentFlag;//���ŵ�ǰ����
    int backNum;
    int volumvFlag;

    QTimer *timer;
    struct SongInfo songInfo;//�洢���������Ϣ

    float lastTime;
};

#endif // MUSIC_H
