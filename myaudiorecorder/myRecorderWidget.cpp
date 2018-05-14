#include "myRecorderWidget.h"
#include "ui_myRecorderWidget.h"
#include <QAudioRecorder>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MyRecorderWidget::MyRecorderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyRecorderWidget)
{
    ui->setupUi(this);

    audioRecorder = new QAudioRecorder;

    QStringList inputs = audioRecorder->audioInputs();
    ui->comboBox->addItems(inputs);

    connect(audioRecorder, &QAudioRecorder::durationChanged, this,
            &MyRecorderWidget::updateProgress);

    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/pcm");
    audioSettings.setQuality(QMultimedia::HighQuality);
    audioRecorder->setAudioSettings(audioSettings);
}

MyRecorderWidget::~MyRecorderWidget()
{
    delete ui;
}

// 选择按钮
void MyRecorderWidget::on_pushButton_clicked()
{
    recorderPath = QFileDialog::getSaveFileName();
    ui->lineEdit->setText(recorderPath);
}

// 开始按钮
void MyRecorderWidget::on_pushButton_2_clicked()
{
    if(recorderPath == "") {
        QMessageBox::warning(this, "WARNING!", "path is NULL!\n Please Input\t", QMessageBox::Ok);
        return ;
    }
    audioRecorder->setAudioInput(ui->comboBox->currentText());
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(recorderPath));
    audioRecorder->record();
    ui->pushButton_2->setText("录制中\b");
}

// 停止按钮
void MyRecorderWidget::on_pushButton_4_clicked()
{
    audioRecorder->stop();
    ui->pushButton_2->setText("开始\b");
    QMessageBox::information(this, "INFO", "录制成功!\t", QMessageBox::Ok);
}

void MyRecorderWidget::updateProgress(qint64 duration)
{
    if (audioRecorder->error() != QMediaRecorder::NoError || duration < 1000)
        return;

    setWindowTitle(tr("Recorded %1 sec").arg(duration / 1000));
}
