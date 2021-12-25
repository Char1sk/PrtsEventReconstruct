#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "pagewelcome.h"
#include "pagemenu.h"
#include "pagestage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showWelcome();
    void showMenu();
    void showStage1();
    void showStage2();
    void showStage(bool isHard);

private:
    Ui::MainWindow *ui;
    PageWelcome *pageWelcome = nullptr;
    PageMenu *pageMenu = nullptr;
    PageStage *pageStage = nullptr;
    QMediaPlayer *mplayer = nullptr;
    QMediaPlaylist *mlist = nullptr;
};

#endif // MAINWINDOW_H
