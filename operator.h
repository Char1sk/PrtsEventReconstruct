#ifndef OPERATOR_H
#define OPERATOR_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QMovie>

#include "enemy.h"

class PageStage;
class Enemy;

class Operator : public QWidget
{
    Q_OBJECT

    friend class PageStage;
    friend class Enemy;

    enum OperatorState {
        idle, attack
    };

public:
    Operator();
    Operator(int px, int py, int nx, int ny, QWidget *p,
             const QVector<QPixmap> &iimgs,
             const QVector<QPixmap> &aimgs);
    ~Operator();
    void updateSelf(const QVector<Enemy*> &enemies);

signals:
    void doAttack(Enemy *en, int x, int y);

private:
    QWidget *parent = nullptr;
    int picx;
    int picy;
    int nowx;
    int nowy;
    int changeCounter = 0;
    int nowFrame = 0;
    OperatorState state = idle;
    Enemy *target = nullptr;
    QVector<QLabel*> idleImages;
    QVector<QLabel*> attackImages;
    QLabel* nowImage = nullptr;
};

#endif // OPERATOR_H
