#include "pagemenu.h"
#include "ui_pagemenu.h"

PageMenu::PageMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageMenu)
{
    ui->setupUi(this);

    backgroundLabel = new QLabel(this);
    QPixmap bgMap(":/images/scene.png");
    backgroundLabel->setPixmap(bgMap);
    backgroundLabel->move(0, 0);
    backgroundLabel->show();

    helpLabel = new QLabel(this);
    QPixmap hpMap(":/images/rules.png");
    helpLabel->setPixmap(hpMap);
    helpLabel->move(110, 150);
    helpLabel->hide();

    stageButton1 = new QPushButton(this);
    stageButton1->setFixedSize(230, 70);
    stageButton1->setStyleSheet(
        "QPushButton{border: none; background-image: url(:/images/Normal.png);}"
        "QPushButton:pressed{border: none; background-image: url(:/images/NormalPressed.png);}"
    );
    stageButton1->move(1100, 150);
    stageButton1->show();

    stageButton2 = new QPushButton(this);
    stageButton2->setFixedSize(230, 70);
    stageButton2->setStyleSheet(
        "QPushButton{border: none; background-image: url(:/images/Hard.png);}"
        "QPushButton:pressed{border: none; background-image: url(:/images/HardPressed.png);}"
    );
    stageButton2->move(1100, 300);
    stageButton2->show();

    helpButton = new QPushButton(this);
    helpButton->setFixedSize(230, 70);
    helpButton->setStyleSheet(
        "QPushButton{border: none; background-image: url(:/images/Help.png);}"
        "QPushButton:pressed{border: none; background-image: url(:/images/HelpPressed.png);}"
    );
    helpButton->move(1100, 450);
    helpButton->show();

    connect(helpButton, QPushButton::clicked, this, showHelp);
}

PageMenu::~PageMenu()
{
    delete ui;
}

void PageMenu::mousePressEvent(QMouseEvent *event)
{
//    if (helpButton && isHelpOn) {
//        isHelpOn = false;
//        helpLabel->hide();
//    }
}

void PageMenu::showHelp()
{
    if (isHelpOn) {
        isHelpOn = false;
        helpLabel->hide();
    } else {
        isHelpOn = true;
        helpLabel->show();
    }
}
