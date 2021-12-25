#ifndef GRID_H
#define GRID_H

#include <QJsonObject>

class PageStage;
class Enemy;

class Grid
{
    friend class PageStage;
    friend class Enemy;

public:
    Grid();
    void loadJson(const QJsonObject& obj);
    void deploy() {canDeploy = false;}
    void retreat() {canDeploy = true;}

private:
    int row;
    int col;
    int centerx = 0;
    int centery = 0;
    bool isUpper;
    bool isLower;
    bool canDeploy;
};

#endif // GRID_H
