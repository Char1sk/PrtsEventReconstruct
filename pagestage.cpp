#include "pagestage.h"
#include "ui_pagestage.h"

#include <QDebug>

PageStage::PageStage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageStage)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    // load pixmaps
    QString kroosIdleFolder = QString(":/images/kroos-idle/");
    for (int i = 0; i < 47; ++i) {
        QPixmap pix(kroosIdleFolder+QString("kroos-idle-%1.png").arg(i));
        pix = pix.scaled(QSize(150,150),Qt::KeepAspectRatio);
        kroosIdleImages.append(pix);
    }
    QString kroosAttackFolder = QString(":/images/kroos-attack/");
    for (int i = 0; i < 17; ++i) {
        QPixmap pix(kroosAttackFolder+QString("kroos-attack-%1.png").arg(i));
        pix = pix.scaled(QSize(160,160),Qt::KeepAspectRatio);
        kroosAttackImages.append(pix);
    }
    QString sodierRunFolder = QString(":/images/sodier-run/");
    for (int i = 0; i < 19; ++i) {
        QPixmap pix(sodierRunFolder+QString("sodier-run-%1.png").arg(i));
        sodierRunImages.append(pix);
    }

    // I FAILED TO CONTROL TIMER
    stageTimer = new QTimer(this);
    stageTimer->setTimerType(Qt::PreciseTimer);
    stageTimer->setInterval(1000/60);
    connect(stageTimer, QTimer::timeout, this, updateStage, Qt::DirectConnection);
    qDebug() << "Stage Cons Called";
}

PageStage::~PageStage()
{
    delete ui;
}

void PageStage::updateStage()
{
//    qDebug() << "Operators";
    foreach (auto ope, operators) {
        if (ope) {
            ope->updateSelf(enemies);
        }
    }
//    qDebug() << "Bullets";
    foreach (auto bul, bullets) {
        if (bul) {
            bul->updateSelf();
        }
    }
//    qDebug() << "Enemies";
    int deadCount = 0;
    foreach (auto ene, enemies) {
        if (ene) {
            ene->updateSelf();
            if (ene->state == Enemy::dead) {
                ++deadCount;
            }
        }
    }
    if (deadCount == enemies.size()) {
        qDebug() << "ALL CLEAR!";
        endStage(true);
    }
//    qDebug() << "Delete Done Bullets";
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        if ((*it)->isDone) {
            auto toRemove = it;
            (*toRemove)->target->nowHealth -= (*toRemove)->damage;
            bullets.erase(toRemove);
            ++it;
        } else {
            ++it;
        }
    }
//    qDebug() << "Delete Done Bullets";
    updateCost();
//    qDebug() << "Update";
    update();
//    static int a = 0;
//    qDebug() << ++a;
}

void PageStage::updateCost()
{
    int maxCounter = (isHard ? 120 : 60);
    if (cost <= 99) {
        costCounter = (costCounter + 1) % maxCounter;
    } else {
        costCounter = maxCounter-1;
    }
    if (costCounter == 0) {
        cost += 1;
    }
}

void PageStage::makeBullet(Enemy *en, int x, int y)
{
    bullets.append(new Bullet(this, en, x, y));
    qDebug() << bullets.size();
}

void PageStage::loadStage(const QString &sid, bool isHard)
{
    this->isHard = isHard;
    stageId = sid;
    stageMap = QPixmap(QString(":/images/%1.png").arg(sid));
    // variables
    QFile inJsonFile;
    QByteArray inJsonData;
    QJsonDocument inJsonDoc;
    // load stage json file
    inJsonFile.setFileName(QString(":/stages/%1.json").arg(sid));
    inJsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    inJsonData = inJsonFile.readAll();
    inJsonDoc = QJsonDocument::fromJson(inJsonData);
    inJsonFile.close();
    // data
    QJsonObject rootObj = inJsonDoc.object();
    rows = rootObj.value("rows").toInt();
    cols = rootObj.value("cols").toInt();
    grids = QVector<QVector<Grid>>(rows, QVector<Grid>(cols));
    const QJsonArray &gridsData = rootObj.value("grids").toArray();
    for (auto it = gridsData.constBegin(); it != gridsData.constEnd(); ++it) {
        int r = it->toObject().value("row").toInt();
        int c = it->toObject().value("col").toInt();
        grids[r][c].loadJson(it->toObject());
    }
    // load enemy json file
//    if (isHard) {
//        inJsonFile.setFileName(QString(":/enemies/%1-hard.json").arg(sid));
//    } else {
        inJsonFile.setFileName(QString(":/enemies/%1.json").arg(sid));
//    }
    inJsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    inJsonData = inJsonFile.readAll();
    inJsonDoc = QJsonDocument::fromJson(inJsonData);
    inJsonFile.close();
    // data
    QJsonArray rootArr = inJsonDoc.array();
    for (auto it = rootArr.constBegin(); it != rootArr.constEnd(); ++it) {
        Enemy *en = new Enemy(this, sodierRunImages);
        en->loadJson(it->toObject(), grids);
//        if (isHard) {
//            en->maxHealth *= 1.1;
//            en->nowHealth *= 1.1;
//        }
        connect(en, Enemy::invade, this, invaded);
        enemies.append(en);
    }

    // let the battle begin
    stageTimer->start();
    qDebug() << "Started";
}

void PageStage::endStage(bool isWin)
{
    stageTimer->stop();
    setAcceptDrops(false);
    QPixmap endMap;
    QLabel *endLabel = new QLabel(this);
    if (isWin) {
        endMap = QPixmap(":/images/Win.png");
        endLabel->setPixmap(endMap);
        endLabel->move(0, 215);
    } else {
        endMap = QPixmap(":/images/Lose.png");
        endLabel->setPixmap(endMap);
        endLabel->move(0, 0);
    }
    endLabel->show();
    QEventLoop eventloop;
    QTimer::singleShot(3000, &eventloop, SLOT(quit()));
    eventloop.exec();
    qDebug() << "stage end";
    emit toMain();
}

void PageStage::invaded()
{
    endStage(false);
}

void PageStage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // Draw background
    painter.drawPixmap(rect(), stageMap, QRect());
    // Draw cost?
    QPixmap cPix(":/images/cost.png");
    painter.drawPixmap(1440-140,810-135-55,140,55,cPix);
    QPen textPen;
    textPen.setColor(QColor(255, 255, 255));
    painter.setPen(textPen);
    painter.setFont(QFont("Times", 28, QFont::Bold));
    painter.drawText(1440-135+70, 810-135-10, QString::number(cost,10));
    QBrush barBrush;
    barBrush.setColor(QColor(255, 255, 255, 0));
    painter.setBrush(barBrush);
    int maxCounter = (isHard ? 120 : 60);
    painter.drawRect(1440-135, 810-135-5, 140.0*costCounter/maxCounter, 5);
    // Draw heads
    QPen headPen;
    headPen.setColor(QColor(107, 107, 107));
    headPen.setWidth(2);
    painter.setPen(headPen);
    QPixmap kPix(":/images/Kroos.png");
    painter.drawPixmap(1440-135, 810-135, 135, 135, kPix);
    painter.drawRect(1440-135, 810-135, 135, 135);
    // No use, why?
//    if (cost < 10) {
//        QBrush maskBrush;
//        maskBrush.setColor(QColor(0, 0, 0, 127));
//        painter.setBrush(maskBrush);
//        painter.drawRect(1440-135, 810-135, 135, 135);
//    }
    // Draw bullets
    QPen bulletPen;
    bulletPen.setColor(Qt::white);
    bulletPen.setWidth(2);
    painter.setPen(bulletPen);
    foreach (auto bul, bullets) {
        if (bul) {
//            qDebug() << "Bullets Drawed";
            painter.drawLine(QPoint(bul->begx,bul->begy),
                             QPoint(bul->endx,bul->endy));
        }
    }


    // Test grid location
//    foreach (const auto &vec, grids) {
//        foreach (const Grid &g, vec) {
//            if (g.centerx && g.centery) {
//                QBrush b = g.isUpper ? Qt::red : Qt::blue;
//                painter.setBrush(b);
//                painter.drawRect(g.centerx-40, g.centery-50, 80, 70);
//                painter.drawEllipse(QPoint(g.centerx, g.centery), 10, 10);
//                // x: -40 +40
//                // y: -50 +20
//            }
//            // * 1.125
//        }
//    }
}


void PageStage::mousePressEvent(QMouseEvent *event)
{
    if (cost < 10)
        return;

    qDebug() << event->pos();
    int x = event->pos().x();
    int y = event->pos().y();
    if (1440-135 <= x && x <= 1440 && 810-135 <= y && y <= 810)
    {
        qDebug() << "In Pic";

        QDrag *drag = new QDrag(this);

        QPixmap dragPix = QPixmap(":/images/alpha-kroos-forward-attack.png");
        dragPix = dragPix.scaled(QSize(150,150),Qt::KeepAspectRatio);
        qDebug() << dragPix.size();////
        dragPixLabel = new QLabel(this);
        dragPixLabel->setPixmap(dragPix);
        dragPixLabel->resize(dragPix.size());
        dragPixLabel->hide();

        QPoint dragPoint(dragPix.width()/2, dragPix.height());

        QByteArray pixData;
        QDataStream pixStream(&pixData, QIODevice::WriteOnly);
        pixStream << dragPix << dragPoint;
        QMimeData *dragData = new QMimeData();
        dragData->setData("pix", pixData);
        drag->setMimeData(dragData);

        auto ret = drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction);
        if (ret == Qt::MoveAction)
            qDebug() << "MOVE";
        else if (ret == Qt::CopyAction)
            qDebug() << "COPY";
        else
            qDebug() << "ELSE";
    }
    else
    {
        qDebug() << "No";
    }
}

void PageStage::dragEnterEvent(QDragEnterEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
    qDebug() << 111;
}

void PageStage::dragMoveEvent(QDragMoveEvent *event)
{
    int index = -1;
    int jndex = -1;
    int nowx = event->pos().x();
    int nowy = event->pos().y();
    bool canDeploy = false;
    bool isUpper = false;
    for (int idx = 0; idx < rows; ++idx) {
        for (int jdx = 0; jdx < cols; ++jdx) {
            const Grid &grid = grids[idx][jdx];
            if (grid.centerx-40 <= nowx && nowx <= grid.centerx+40 &&
                    grid.centery-50 <= nowy && nowy <= grid.centery+20) {
                index = idx;
                jndex = jdx;
                canDeploy = grid.canDeploy;
                isUpper = grid.isUpper;
                break;
            }
        }
    }


    QByteArray pixData = event->mimeData()->data("pix");
    QDataStream pixStream(&pixData, QIODevice::ReadOnly);
    QPixmap pixMap;
    QPoint pixPoint;
    pixStream >> pixMap >> pixPoint;
    if (canDeploy && isUpper) {
//        qDebug() << "I'm in rect: " << index;

        const Grid &grid = grids[index][jndex];
        dragPixLabel->hide();

        QPoint point;
        point.rx() = grid.centerx - pixPoint.x();
        point.ry() = grid.centery - pixPoint.y();

        if (!nowLabel) {
            nowLabel = new QLabel(this);
            nowLabel->setPixmap(pixMap);
            nowLabel->resize(pixMap.size());
            nowLabel->move(point);
            nowLabel->show();
        }
        //        if (nowLabel)
        //        {
        //            qDebug() << "Also I am deleting";
        //            nowLabel->close();
        //            delete nowLabel;
        //        }
    } else {
//        qDebug() << "I'm out of rect: " << index;
//        dragPixLabel->setPixmap(pixMap);
//        dragPixLabel->resize(pixMap.size());
        dragPixLabel->move(event->pos()-pixPoint);
        dragPixLabel->show();

        if (nowLabel) {
            qDebug() << "Also I am deleting";
            nowLabel->close();
            delete nowLabel;
            nowLabel = nullptr;
        }
    }
}

void PageStage::dropEvent(QDropEvent *event)
{
//    event->setDropAction(Qt::MoveAction);
//    event->accept();
    qDebug() << "Dropping";

    dragPixLabel->close();
    delete dragPixLabel;
    dragPixLabel = nullptr;
    if (nowLabel && event->mimeData()->hasFormat("pix")) {
        qDebug() << "Has Pix";


        int nowx = event->pos().x();
        int nowy = event->pos().y();
        int centerx = 0;
        int centery = 0;
        for (int idx = 0; idx < rows; ++idx) {
            for (int jdx = 0; jdx < cols; ++jdx) {
                const Grid &grid = grids[idx][jdx];
                if (grid.centerx-40 <= nowx && nowx <= grid.centerx+40 &&
                        grid.centery-50 <= nowy && nowy <= grid.centery+20) {
                    grids[idx][jdx].canDeploy = false;
                    centerx = grid.centerx;
                    centery = grid.centery;
                    break;
                }
            }
        }

//        QByteArray pixData = event->mimeData()->data("pix");
//        QDataStream pixStream(&pixData, QIODevice::ReadOnly);
//        QPixmap pixMap;
//        QPoint pixPoint;
//        pixStream >> pixMap >> pixPoint;

        // leave the pixmap
//        QLabel *pixLabel = new QLabel(this);
//        pixLabel->setPixmap(*(nowLabel->pixmap()));
//        pixLabel->resize(nowLabel->size());
//        pixLabel->move(nowLabel->pos());
//        pixLabel->show();

        if (cost >= 10) {
            cost -= 10;
        } else {
            nowLabel->close();
            delete nowLabel;
            nowLabel = nullptr;
            return;
        }

        Operator *newOpe = new Operator(nowLabel->x(), nowLabel->y(), centerx, centery,
                                        this, kroosIdleImages, kroosAttackImages);
        connect(newOpe, Operator::doAttack, this, makeBullet);
        operators.append(newOpe);

//        QLabel *pixLabel = new QLabel(*nowLabel);
//        pixLabel->show();

        nowLabel->close();
        delete nowLabel;
        nowLabel = nullptr;

        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        qDebug() << "No Pix";
        event->ignore();
    }
}
