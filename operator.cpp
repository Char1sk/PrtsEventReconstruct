#include "operator.h"
#include <QDebug>

Operator::Operator() :
    QWidget(nullptr)
{

}

Operator::Operator(int px, int py, int nx, int ny, QWidget *p,
                   const QVector<QPixmap> &iimgs,
                   const QVector<QPixmap> &aimgs) :
    QWidget(p),
    picx(px),
    picy(py),
    nowx(nx),
    nowy(ny),
    parent(p)
{
    for (int i = 0; i < iimgs.size(); ++i) {
        QLabel *pl = new QLabel(p);
        pl->setPixmap(iimgs[i]);
        pl->move(picx, picy);
        pl->hide();
        idleImages.append(pl);
    }
    for (int i = 0; i < aimgs.size(); ++i) {
        QLabel *pl = new QLabel(p);
        pl->setPixmap(aimgs[i]);
        pl->move(picx-10, picy);
        pl->hide();
        attackImages.append(pl);
    }
    nowFrame = 0;
    nowImage = idleImages[nowFrame];
    nowImage->show();

}

Operator::~Operator()
{
    for (int i = 0; i < idleImages.size(); ++i) {
        delete idleImages[i];
    }
}

void Operator::updateSelf(const QVector<Enemy*> &enemies)
{
    changeCounter = (changeCounter + 1) % 2;
    // real change
    if (changeCounter == 0) {
        nowImage->hide();
        // do state change
        bool noTarget = true;
        foreach (Enemy *en, enemies) {
            // somebody in attack range
            if (en->state == Enemy::alive &&
                nowx- 50 <= en->nowx && en->nowx <= nowx+450 &&
                nowy-150 <= en->nowy && en->nowy <= nowy+150) {
                // become attack
                if (target != en) {
                    qDebug() << "In attack";
                    target = en;
                    state = attack;
                    nowFrame = 0;
                }
                noTarget = false;
                break;
            }
        }
        // become idle
        if (state == attack && noTarget) {
            qDebug() << "No Target";
            target = nullptr;
            state = idle;
            nowFrame = 0;
        }
        // act with state
        if (state == idle) {
            nowFrame = (nowFrame + 1) % idleImages.size();
            nowImage = idleImages[nowFrame];
        } else if (state == attack) {
            nowFrame = (nowFrame + 1) % attackImages.size();
            nowImage = attackImages[nowFrame];
            if (nowFrame == 11) {
                qDebug() << "Attack!";
                emit doAttack(target, nowx+80, nowy-75);
            }
        }
        nowImage->show();
    }
}
