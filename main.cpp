#include "mainwindow.h"
#include <QApplication>

#include "pagewelcome.h"

#include <QString>
#include <QWidget>
#include <QLabel>
#include <QMovie>

#include <QLinkedList>
#include <QDebug>

#include <QMediaPlayer>
#include <QMediaPlaylist>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QMediaPlaylist *mlist = new QMediaPlaylist();
//    QMediaPlayer *mplayer = new QMediaPlayer();
//    mlist->addMedia(QUrl("qrc:/music/welcome.mp3"));
//    mlist->addMedia(QUrl("qrc:/music/menu.mp3"));
//    mlist->addMedia(QUrl("qrc:/music/1-7.mp3"));
//    mlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
//    mlist->setCurrentIndex(1);
////    mplayer->setMedia(QUrl("qrc:/music/welcome.mp3"));
//    mplayer->setPlaylist(mlist);
//    mplayer->play();

    MainWindow w;
    w.show();

    return a.exec();
//    QLinkedList<int> qll({1, 9, 2, 8, 3, 7, 4, 6, 5});
//    QLinkedList<int> qll({1, 2, 3, 4, 5, 6, 7, 8, 9});
//    QLinkedList<int> qll({1});
//    for (auto it = qll.begin(); it != qll.end(); ) {
//        if (*it <= 5) {
//            auto toRemove = it;
//            ++it;
//            qll.erase(toRemove);
//        } else {
//            ++it;
//        }
//    }
//    foreach (int val, qll) {
//        qDebug() << val;
//    }
}
