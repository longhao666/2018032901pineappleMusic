#include "databasedriver.h"
#include "ui_databasedriver.h"
#include <QDir>
#include <QPainter>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QTime>
#include <QSqlRecord>
#include <QPaintEvent>

DatabaseDriver::DatabaseDriver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::databaseDriver)
{
    ui->setupUi(this);

    this->setWindowTitle("  登录  ");

    ui->userlineEdit->setPlaceholderText(tr("请输入5-15用户名"));
    ui->passwordlineEdit_2->setPlaceholderText(tr("请输入6位密码"));

    QSqlDatabase db = QSqlDatabase::database("lh1");
    query = new QSqlQuery(db);

    connect(ui->quitpushButton, &QPushButton::clicked, this, &DatabaseDriver::slotQuitClicked);
    connect(ui->logInpushButton_2, &QPushButton::clicked, this, &DatabaseDriver::slotLogInClicked);
    connect(ui->enterpushButton_2, &QPushButton::clicked, this, &DatabaseDriver::slotEnterClicked);
    connect(ui->forgetpushButton_3, &QPushButton::clicked, this, &DatabaseDriver::slotForgetClicked);

    ui->forgetpushButton_3->setEnabled(false);
}

DatabaseDriver::~DatabaseDriver()
{
    qDebug() << "DatabaseDriver::~DatabaseDriver()";
    delete ui;
    delete query;
}

void DatabaseDriver::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 绘制图标
    painter.drawPixmap(rect(), QPixmap(":/new/image/pic/background.png"));
}

void DatabaseDriver::slotLogInClicked()
{
#if 0
    qDebug() << "void databaseDriver::slotLogInClicked()";
#endif
    QString s1 = ui->userlineEdit->text();
    QString s2 = ui->passwordlineEdit_2->text();
    int re = logInUser(*query, s1, s2);
    if(re == 0) {
        QMessageBox::warning(this, "information", "注册成功！  ", QMessageBox::Ok);
    }else if(re == 1) {
        QMessageBox::information(this, "information", "注册失败，请输入用户名   ", QMessageBox::Ok);
    }else if(re == 2) {
        QMessageBox::information(this, "information", "注册失败，请输入密码   ", QMessageBox::Ok);
    }else if(re == 4) {
        QMessageBox::information(this, "information", "注册失败，用户名存在或密码不对，请重新输入   ", QMessageBox::Ok);
    }
#if 0
    ui->userlineEdit->clear();
    ui->passwordlineEdit_2->clear();
#endif
}

void DatabaseDriver::slotQuitClicked()
{
    qDebug() << "void databaseDriver::slotQuitClicked()";
//    this->hide();
    emit signalQuitClicked();
}

void DatabaseDriver::slotEnterClicked()
{
    QString s1 = ui->userlineEdit->text();
    QString s2 = ui->passwordlineEdit_2->text();
    int re = entertUserAndPassword(*query, s1, s2);
    if(re == 0) {
//        QMessageBox::information(this, "information", "登录成功!   ", QMessageBox::Ok);
        ui->userlineEdit->clear();
        ui->passwordlineEdit_2->clear();
        emit signalEnterClicked();
    }else if(re == 4) {
        QMessageBox::information(this, "information", "用户名或密码错误!   ", QMessageBox::Ok);
    }else if(re == 1) {
        QMessageBox::warning(this, "information", "请输入用户名或密码！  ", QMessageBox::Ok);
    }
}

void DatabaseDriver::slotForgetClicked()
{

}
