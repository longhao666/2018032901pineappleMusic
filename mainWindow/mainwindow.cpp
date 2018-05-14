#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "musicplayer.h"

#include <QPushButton>
#include <QLabel>

#define BOTTOM 65
#define TOPLABEL 550

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("pineappleMusic"));
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowShadeButtonHint);

#if 0
    QMenu *printMenu = ui->menuBar->addMenu(tr("编辑(&E)")); // 添加编辑菜单
    QAction *action_print = new QAction(tr("打印"),this);
    QAction *action_printPreview = new QAction(tr("打印预览"),this);
    QAction *action_pdf = new QAction(tr("生成pdf"),this);
    QActionGroup *group = new QActionGroup(this);           // 建立动作组
    group->addAction(action_print);
    action_print->setCheckable(true);
    group->addAction(action_printPreview);
    action_printPreview->setCheckable(true);
    group->addAction(action_pdf);
    action_pdf->setCheckable(true);
    action_pdf->setChecked(true);
    printMenu->addAction(action_print);
    printMenu->addAction(action_printPreview);
    printMenu->addAction(action_pdf);
#endif
#if 0
    QMenu *printMenu = ui->menuBar->addMenu(tr("编辑(&E)")); // 添加编辑菜单
    QActionGroup *group = new QActionGroup(this);           // 建立动作组
    QAction *action_print = group->addAction(tr("打印"));
    action_print->setCheckable(true);
    QAction *action_printPreview = group->addAction(tr("打印预览"));
    action_printPreview->setCheckable(true);
    QAction *action_pdf = group->addAction(tr("生成pdf"));
    action_pdf->setCheckable(true);
    action_pdf->setChecked(true);

    printMenu->addAction(action_print);
    printMenu->addAction(action_printPreview);
    printMenu->addAction(action_pdf);
#endif

#if 1
    //QMenu *musicMenu = ui->menuBar->addMenu(tr("music(&M)"));

    l1 = new QLabel(this);
    l1->setStyleSheet("background-color:rgba(255, 255, 255, 0)");
    l1->setMinimumWidth(TOPLABEL);

    QAction *qing1 = new QAction("青苹果音乐\b",this);
    qing1->setEnabled(false);
    QFont f1;
    f1.setFamily("黑体");
    f1.setBold(true);
    f1.setWordSpacing(2.5);
    f1.setItalic(true);
    f1.setPixelSize(20);
    qing1->setFont(f1);

    p2 = new QPushButton("退出\b",this);
    //QAction *qing2 = new QAction(tr("退出\b"),this);
    connect(p2, &QPushButton::clicked, this, &MainWindow::slotQuitAction);

    QAction *musicAction = new QAction(tr("music"),this);
    connect(musicAction, &QAction::triggered, this, &MainWindow::slotMusicAction);
    QAction *MVAction= new QAction(tr("MV"),this);
    connect(MVAction, &QAction::triggered, this, &MainWindow::slotMVAction);
    QAction *kGe = new QAction("录歌", this);
    connect(kGe, &QAction::triggered, this, &MainWindow::slotKGeAction);

    QActionGroup *group = new QActionGroup(this);           // 建立动作组
    group->addAction(musicAction);
    musicAction->setCheckable(true);
    group->addAction(MVAction);
    MVAction->setCheckable(true);
    group->addAction(kGe);
    kGe->setCheckable(true);
    musicAction->setChecked(true);


    //musicMenu->addAction(musicAction);
    //musicMenu->addAction(MVAction);
    ui->mainToolBar->setMovable(false);
    ui->mainToolBar->setMinimumHeight(50);
    ui->mainToolBar->addAction(qing1);
    ui->mainToolBar->addAction(musicAction);
    ui->mainToolBar->addAction(MVAction);
    ui->mainToolBar->addAction(kGe);
    ui->mainToolBar->addWidget(l1);
    ui->mainToolBar->addWidget(p2);
#endif

    musicPlayer = new MusicPlayer(ui->centralWidget);
    musicPlayer->setGeometry(0, 0, this->width(), this->height()-BOTTOM);
#if 0
    connect(this, &MainWindow::signalMainWidgetChange, musicPlayer, &MusicPlayer::slotStopClicked);
#elif 1
    connect(this, SIGNAL(signalMainWidgetChange()), musicPlayer, SLOT(slotStopClicked()));
#endif


    player = new Player(ui->centralWidget);
    player->setGeometry(0, 0, this->width(), this->height()-BOTTOM);
    player->player->setVolume(20);

    recorder = new MyRecorderWidget(ui->centralWidget);
    //recorder->setGeometry(0, 0, this->width(), this->height()-BOTTOM);
    recorder->move((this->width() - recorder->width())/2, (this->height() - recorder->height())/2 - 50);
    recorder->hide();

    databaseDriver = new DatabaseDriver();
#if 0
    connect(databaseDriver, &DatabaseDriver::signalQuitClicked, this, &MainWindow::slotWidgetClost);
    connect(databaseDriver, &DatabaseDriver::signalEnterClicked, this, &MainWindow::slotPlayerShow);
#elif 1
    connect(databaseDriver, SIGNAL(signalEnterClicked()), this, SLOT(slotPlayerShow()));
    connect(databaseDriver, SIGNAL(signalQuitClicked()), this, SLOT(slotWidgetClost()));
#endif

    this->slotEnterWidget();

}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow::~MainWindow()";
    delete ui;
    delete databaseDriver;
}

void MainWindow::slotEnterWidget()
{
    //p1->setEnabled(false);
    this->hide();
    databaseDriver->show();
    emit signalMainWidgetChange(0);
    player->player->stop();
}

void MainWindow::slotMusicWidget()
{

}

void MainWindow::slotPlayerShow()
{
    //p1->setEnabled(true);
    this->show();
    databaseDriver->hide();
    this->slotMusicAction();
}

void MainWindow::slotWidgetClost()
{
    databaseDriver->close();
}

void MainWindow::slotMusicAction()
{
    qDebug() << "this is void MainWindow::slotMusicAction()";
    player->hide();
    musicPlayer->show();
    player->player->stop();
    recorder->hide();

}

void MainWindow::slotMVAction()
{
    qDebug() << "this is void MainWindow::slotMVAction()";
    player->show();
    musicPlayer->hide();
    recorder->hide();
    emit signalMainWidgetChange(0);
}

void MainWindow::slotQuitAction()
{
    this->close();
}

void MainWindow::slotKGeAction()
{
    player->hide();
    musicPlayer->hide();
    recorder->show();
}
