#ifndef PAGEMENU_H
#define PAGEMENU_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QMouseEvent>

namespace Ui {
class PageMenu;
}

class PageMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PageMenu(QWidget *parent = 0);
    ~PageMenu();
    bool isHelpOn = false;
    QLabel *backgroundLabel;
    QLabel *helpLabel;
    QPushButton *stageButton1;
    QPushButton *stageButton2;
    QPushButton *helpButton;
    QPushButton *exitButton;

    void mousePressEvent(QMouseEvent *event);

    void showHelp();


private:
    Ui::PageMenu *ui;
};

#endif // PAGEMENU_H
