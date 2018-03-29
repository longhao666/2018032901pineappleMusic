#include "databasedriver.h"
#include "ui_databasedriver.h"
#include <QDir>


DatabaseDriver::DatabaseDriver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::databaseDriver)
{
    ui->setupUi(this);
    this->setWindowTitle("  登录  ");

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

void DatabaseDriver::slotLogInClicked()
{
#if 0
    qDebug() << "void databaseDriver::slotLogInClicked()";
#endif
    QString s1 = ui->userlineEdit->text();
    QString s2 = ui->passwordlineEdit_2->text();
    if(!logInUser(*query, s1, s2)) {
        QMessageBox::warning(this, "waring", "user is exist,failed");
    }else {
        QMessageBox::information(this, "information", "logIn is successed");    
    }
}

void DatabaseDriver::slotQuitClicked()
{
    qDebug() << "void databaseDriver::slotQuitClicked()";
//    this->close();
    emit signalQuitClicked();
}

void DatabaseDriver::slotEnterClicked()
{
    QString s1 = ui->userlineEdit->text();
    QString s2 = ui->passwordlineEdit_2->text();
    if(!entertUserAndPassword(*query, s1, s2)) {
        QMessageBox::warning(this, "waring", "failed! ");
    }else {
        QMessageBox::information(this, "information", "successed! ");
        emit signalEnterClicked();
        this->hide();
    }
//    ui->userlineEdit->clear();
    ui->passwordlineEdit_2->clear();
}

void DatabaseDriver::slotForgetClicked()
{

}
