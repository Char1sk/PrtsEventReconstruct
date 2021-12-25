#include "bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(QWidget *p, Enemy *t, int bx, int by) :
    QWidget(p),
    parent(p),
    target(t),
    begx(bx),
    begy(by)
{
    int tarx = t->nowx+50;
    int tary = t->nowy;
    endx = 0.75 * begx + 0.25 * tarx;
    endy = 0.75 * begy + 0.25 * tary;
    deltax = endx - begx;
    deltay = endy - begy;
}

//void Bullet::paintEvent(QPaintEvent *event)
//{
//    // create pen
//    QPen pen;
//    pen.setColor(Qt::white);
//    pen.setWidth(50);
//    // create painter
//    QPainter painter(parent);
//    painter.setPen(pen);
//    // do painting
//    painter.drawLine(QPoint(begx,begy), QPoint(endx,endy));
//}

void Bullet::updateSelf()
{
    if (target) {
        int tarx = target->nowx;
        int tary = target->nowy - 50;
        // move end point
        if (endx <= tarx - speed) {
            endx += speed;
        } else if (endx > tarx) {
            endx -= speed;
        }
        if (endy <= tary - speed) {
            endy += speed;
        } else if (endy > tary) {
            endy -= speed;
        }
        // move beg point
        begx = endx - deltax;
        begy = endy - deltay;
        // judge
        if (tarx-speed < endx && endx < tarx+speed &&
            tary-speed < endy && endy < tary+speed) {
            isDone = true;
        }
    }
}
