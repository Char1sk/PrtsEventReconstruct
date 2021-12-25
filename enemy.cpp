#include "enemy.h"
#include <QDebug>

Enemy::Enemy()
{

}

Enemy::Enemy(QWidget *p, const QVector<QPixmap> &rimgs) :
    parent(p)
{
    // set speed
    speed = 1;
    // set picx picy nowx nowy
    // set index
    nextIdx = 0;
    // set points
    // set image
    for (int i = 0; i < rimgs.size(); ++i) {
        QLabel *pl = new QLabel(p);
        pl->setPixmap(rimgs[i]);
        pl->hide();
        runImages.append(pl);
    }
    nowCount = rimgs.size();
    nowImage = runImages[0];
    healthSlot = new QLabel(p);
    healthSlot->setStyleSheet("QLabel{background-color:rgb(89,73,50);}");
    healthSlot->hide();
    healthBar = new QLabel(p);
    healthBar->setStyleSheet("QLabel{background-color:rgb(221,106,54);}");
    healthBar->hide();
//    nowImage = new QLabel(p);
//    QPixmap pix = QPixmap(":/images/kroos-idle/kroos-idle-0.png");
//    pix = pix.scaled(QSize(150,150),Qt::KeepAspectRatio);
//    nowImage->setPixmap(pix);
//    nowImage->hide();

}

Enemy::~Enemy()
{
    for (int i = 0; i < nowCount; ++i) {
        delete runImages[i];
    }
}

void Enemy::updateSelf()
{
    ++totalCounter;
    // activate
    if (totalCounter >= time && state == out) {
        qDebug() << "Alive";
        state = alive;
    }
    // die
    if (nowHealth <= 0 && state == alive) {
        die();
    }
    // moving
    if (state == alive) {
        // change pic
        changeCounter = (changeCounter + 1) % 3;
        if (changeCounter == 0) {
            nowFrame = (nowFrame + 1) % nowCount;
            nowImage->hide();
            nowImage = runImages[nowFrame];
            nowImage->show();
        }
        healthSlot->show();
        healthSlot->move(nowx-70-2, nowy+10-1);
        healthSlot->resize(150+4, 10+2);
        healthBar->show();
        healthBar->move(nowx-70, nowy+10);
        healthBar->resize(150.0*nowHealth/maxHealth, 10);
        // next point
        int nextx = points[nextIdx].x();
        int nexty = points[nextIdx].y();
        // only move on one axis
        if (nextx < nowx) {
            picx -= speed;
            nowx -= speed;
        } else if (nextx > nowx) {
            picx += speed;
            nowx += speed;
        } else if (nexty < nowy) {
            picy -= speed;
            nowy -= speed;
        } else if (nexty > nowy) {
            picy += speed;
            nowy += speed;
        }
        // change of point
        if (nextx == nowx && nexty == nowy) {
            ++nextIdx;
            if (nextIdx == points.size()) {
                die();
                emit invade();
                qDebug() << "END!!!";
//                nowx = points[0].x();
//                nowy = points[0].y();
//                picx = nowx - 100;
//                picy = nowy - 180;
//                nextIdx = 1;
            }
        }
        nowImage->move(picx, picy);
    }

}

void Enemy::loadJson(const QJsonObject &obj,
                     const QVector<QVector<Grid>> &grids)
{
    time = 60 * obj.value("time").toInt();
    maxHealth = obj.value("health").toInt();
    nowHealth = maxHealth;
    QJsonArray arr = obj.value("points").toArray();
    for (auto it = arr.constBegin(); it != arr.constEnd(); ++it) {
        qDebug() << *it;
        int row = it->toObject().value("row").toInt();
        int col = it->toObject().value("col").toInt();
        int x = grids[row][col].centerx;
        int y = grids[row][col].centery;
        points.append(QPoint(x,y));
    }
    nowx = points[0].x();
    nowy = points[0].y();
    picx = nowx - 100;
    picy = nowy - 180;
    nextIdx = 1;
}

void Enemy::die()
{
    qDebug() << "Died";
    state = dead;
    nowImage->hide();
    healthSlot->hide();
    healthBar->hide();
}
