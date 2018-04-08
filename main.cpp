#include "mainwindow.h"
#include <QApplication>

#define QS 1

#if QS
#include <QSplashScreen>
#endif


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if QS
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/b1.png"));//设置图片
    splash->show();//显示图片
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."),topRight, Qt::white);//显示信息
//    MainWindow mainWin;
//    splash->showMessage(QObject::tr("Loading modules..."),
//                        topRight, Qt::white); //显示信息
//    loadModules();
//    splash->showMessage(QObject::tr("Establishing connections..."),
//                        topRight, Qt::white); //显示信息
//    establishConnections();
//    mainWin.show();
//    splash->finish(&mainWin);//图片一直显示到mainWin加载完成
//    delete splash;//释放空间，节省内存
#endif
    if(!createConnection()) {
        return 1;
    }
    QSqlDatabase db = QSqlDatabase::database("lh1");
    QSqlQuery query(db);

    query.exec("select * from user");
    while(query.next()) {
        qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
    }
    MainWindow w;
//    w.show();

    return a.exec();
}
