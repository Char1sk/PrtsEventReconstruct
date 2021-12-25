#include "grid.h"

Grid::Grid()
{

}

void Grid::loadJson(const QJsonObject &obj)
{
    row = obj.value("row").toInt();
    col = obj.value("col").toInt();
    centerx = obj.value("centerx").toInt();
    centery = obj.value("centery").toInt();
    isUpper = obj.value("isUpper").toBool();
    isLower = obj.value("isLower").toBool();
    canDeploy = obj.value("canDeploy").toBool();
}


