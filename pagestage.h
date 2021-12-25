#ifndef PAGESTAGE_H
#define PAGESTAGE_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QTimer>
#include <QTime>

#include <QString>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QLinkedList>
#include <QtAlgorithms>

#include <QDrag>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>

#include "grid.h"
#include "operator.h"
#include "enemy.h"
#include "bullet.h"

namespace Ui {
class PageStage;
}

class PageStage : public QWidget
{
    Q_OBJECT

public:
    explicit PageStage(QWidget *parent = 0);
    ~PageStage();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);


    void updateCost();
    void loadStage(const QString &sid, bool isHard);
    void endStage(bool isWin);

public slots:
    void invaded();
    void updateStage();
    void makeBullet(Enemy *en, int x, int y);

signals:
    void toMain();

private:
    Ui::PageStage *ui;
    QString stageId;
    QPixmap stageMap;
    bool isHard = false;
    int cost = 10;
    int costCounter = 0;
    int rows;
    int cols;
    // something for running
    QTimer *stageTimer;
    QLabel *nowLabel = nullptr;
    QLabel *dragPixLabel = nullptr;
    // containers for elements
    QVector<QVector<Grid>> grids;
    QVector<Operator*> operators;
    QVector<Enemy*> enemies;
    QLinkedList<Bullet*> bullets;
    // loaded for other objects
    QVector<QPixmap> kroosIdleImages;
    QVector<QPixmap> kroosAttackImages;
    QVector<QPixmap> sodierRunImages;
//    QThread *timerThread;
};

#endif // PAGESTAGE_H
