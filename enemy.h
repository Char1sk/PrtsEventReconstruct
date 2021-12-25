#ifndef ENEMY_H
#define ENEMY_H

#include <QLabel>
#include <QPixmap>
#include <QPoint>
#include <QVector>
#include <QJsonArray>
#include <QJsonObject>

#include "grid.h"

class PageStage;
class Operator;
class Bullet;

class Enemy : public QObject
{
    Q_OBJECT

    friend class PageStage;
    friend class Operator;
    friend class Bullet;

    enum EnemyState {
        out, alive, dead
    };

public:
    Enemy();
    Enemy(QWidget *p, const QVector<QPixmap> &rimgs);
    ~Enemy();
    void updateSelf();
    void loadJson(const QJsonObject &obj,
                  const QVector<QVector<Grid>> &grids);
    void die();

signals:
    void invade();

private:
    QWidget *parent = nullptr;
    int time;
    int speed;
    int picx;
    int picy;
    int nowx;
    int nowy;
    int nextIdx;
    QVector<QPoint> points;
    QLabel* nowImage = nullptr;
    QLabel* healthBar = nullptr;
    QLabel* healthSlot = nullptr;
    QVector<QLabel*> runImages;
    int totalCounter = 0;
    int changeCounter = 0;
    int nowFrame = 0;
    int nowCount = 0;
    EnemyState state = out;
    int maxHealth;
    int nowHealth;

//    int x;
//    int y;
//    int changeCounter = 0;
//    int nowFrame = 0;
//    QWidget *parent = nullptr;
//    int nowCount;
//    QVector<QLabel*> idleImages;
//    QLabel* nowImage = nullptr;
};

#endif // ENEMY_H
