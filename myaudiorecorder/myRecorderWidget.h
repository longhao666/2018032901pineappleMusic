#ifndef myRecorderWidget_H
#define myRecorderWidget_H

#include <QWidget>
class QAudioRecorder;

namespace Ui {
class MyRecorderWidget;
}

class MyRecorderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyRecorderWidget(QWidget *parent = 0);
    ~MyRecorderWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void updateProgress(qint64 duration);

private:
    Ui::MyRecorderWidget *ui;

    QAudioRecorder *audioRecorder;
    QString recorderPath;
};

#endif // myRecorderWidget_H
