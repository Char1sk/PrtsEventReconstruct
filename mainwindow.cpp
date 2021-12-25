#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/PRTS.png"));
    setWindowTitle("PRTS事相重建");
    setGeometry(240, 100, 1440, 810);
    setFixedSize(1440, 810);

    mlist = new QMediaPlaylist();
    mlist->addMedia(QUrl("qrc:/music/welcome.mp3"));
    mlist->addMedia(QUrl("qrc:/music/menu.mp3"));
    mlist->addMedia(QUrl("qrc:/music/1-7.mp3"));
    mlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    mplayer = new QMediaPlayer();
    mplayer->setPlaylist(mlist);
    mplayer->play();

    showWelcome();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showWelcome()
{
//    if (mplayer->state() == QMediaPlayer::PlayingState) {
//        mplayer->stop();
//    }
    mlist->setCurrentIndex(0);
    qDebug() << "Trying to switch main";
    // Wrong for no reason
//    if (pageWelcome) {
//        delete pageWelcome;
//    }
    pageWelcome = new PageWelcome();
    setCentralWidget(pageWelcome);
    connect(pageWelcome->beginButton, QPushButton::clicked, this, showMenu);
//    mplayer->setMedia(QUrl::fromLocalFile("D:\\the_remote_city\\Qt\\PrtsEventReconstructCopy\\music\\welcome.mp3"));
    mplayer->play();
//    connect(pageWelcome->beginButton, QPushButton::clicked, this, showStage);
}

void MainWindow::showMenu()
{
//    if (mplayer->state() == QMediaPlayer::PlayingState) {
//        mplayer->stop();
//    }
    mlist->setCurrentIndex(1);
    qDebug() << "Trying to switch menu";
    pageMenu = new PageMenu();
    setCentralWidget(pageMenu);
    connect(pageMenu->stageButton1, QPushButton::clicked, this, showStage1);
    connect(pageMenu->stageButton2, QPushButton::clicked, this, showStage2);
//    mplayer->setMedia(QUrl::fromLocalFile("D:\\the_remote_city\\Qt\\PrtsEventReconstructCopy\\music\\menu.mp3"));
    mplayer->play();
}

void MainWindow::showStage1()
{
    showStage(false);
}

void MainWindow::showStage2()
{
    showStage(true);
}

void MainWindow::showStage(bool isHard)
{
    mlist->setCurrentIndex(2);
    qDebug() << "Trying to switch stage 1-7" << isHard;
    pageStage = new PageStage();
    pageStage->loadStage("1-7", isHard);
    setCentralWidget(pageStage);
    connect(pageStage, PageStage::toMain, this, showMenu);
    mplayer->play();
}
