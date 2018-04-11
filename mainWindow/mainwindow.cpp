#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

#include "musicplayer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    QMenu *musicMenu = ui->menuBar->addMenu(tr("music(&M)"));
    QAction *musicAction = new QAction(tr("music"),this);
    connect(musicAction, &QAction::triggered, this, slotMusicAction);
    QAction *MVAction= new QAction(tr("MV"),this);
    connect(MVAction, &QAction::triggered, this, slotMVAction);

    QActionGroup *group = new QActionGroup(this);           // 建立动作组
    group->addAction(musicAction);
    musicAction->setCheckable(true);
    group->addAction(MVAction);
    MVAction->setCheckable(true);
    musicAction->setChecked(true);
    musicMenu->addAction(musicAction);
    musicMenu->addAction(MVAction);

    ui->mainToolBar->setMovable(false);

    musicPlayer = new MusicPlayer(this);
    musicPlayer->setGeometry(0, 50, this->width(), this->height()-50);
#if 0
    connect(this, &MainWindow::signalMainWidgetChange, musicPlayer, &MusicPlayer::slotStopClicked);
#elif 1
    connect(this, SIGNAL(signalMainWidgetChange()), musicPlayer, SLOT(slotStopClicked()));
#endif

    p1 = new QPushButton(tr("退出"), this);
    ui->mainToolBar->addWidget(p1);
    connect(p1, &QPushButton::clicked, this, &MainWindow::slotEnterWidget);

    player = new Player(ui->centralWidget);
    player->setGeometry(0, 0, this->width(), this->height()-50);
    player->player->setVolume(20);



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
    p1->setEnabled(false);
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
    p1->setEnabled(true);
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

}

void MainWindow::slotMVAction()
{
    qDebug() << "this is void MainWindow::slotMVAction()";
    player->show();
    musicPlayer->hide();
    emit signalMainWidgetChange(0);
}
