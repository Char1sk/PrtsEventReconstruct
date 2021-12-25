#ifndef BULLET_H
#define BULLET_H

#include <QWidget>
#include <QLabel>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

#include "enemy.h"

class PageStage;
class Enemy;

class Bullet : public QWidget
{
    friend class PageStage;
    friend class Enemy;

public:
    Bullet();
    Bullet(QWidget *p, Enemy *t, int bx, int by);
//    void paintEvent(QPaintEvent *event);
    void updateSelf();

private:
    QWidget *parent = nullptr;
    Enemy *target = nullptr;
    QLabel *label = nullptr;
    int damage = 100;
    int speed = 10;
    int begx;
    int begy;
    int endx;
    int endy;
    int deltax;
    int deltay;
    bool isDone = false;
};

#endif // BULLET_H
