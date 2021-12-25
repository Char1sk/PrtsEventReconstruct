#include "pagewelcome.h"
#include "ui_pagewelcome.h"

#include <QDebug>

PageWelcome::PageWelcome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageWelcome)
{
    ui->setupUi(this);
    // 最外层布局
    QVBoxLayout *vlay = new QVBoxLayout();
    vlay->setMargin(0);
    vlay->setSpacing(0);
    // 上边缘
    QLabel *lab1 = new QLabel(this);
    lab1->setStyleSheet("QLabel{background:#3f3f3f;}");
    // 中间组件
    QWidget *wid = new QWidget(this);
    wid->setStyleSheet("background:#e9e9e9");
        // 中间组件的垂直布局
        QVBoxLayout *wlay = new QVBoxLayout();
        wlay->setMargin(0);
        wlay->setSpacing(0);
        // 载入PRTS大图标
        QLabel *iconLabel = new QLabel();
        QPixmap iconMap = QPixmap(":/images/alphaPRTS.png");
        iconMap = iconMap.scaled(250, 250, Qt::KeepAspectRatio);
        iconLabel->setPixmap(iconMap);
        // 载入事项重建标题
        QLabel *titleLabel = new QLabel();
        QPixmap titleMap = QPixmap(":/images/Title.png");
        titleLabel->setPixmap(titleMap);
        // 载入开始按钮图标
//        QPushButton *beginButton = new QPushButton();
        beginButton = new QPushButton();
        beginButton->setFixedSize(240, 90);
        beginButton->setStyleSheet(
            "QPushButton{border: none; background-image: url(:/images/Begin.png);}"
            "QPushButton:pressed{border: none; background-image: url(:/images/BeginPressed.png);}"
        );
//        connect(beginButton, &QPushButton::clicked, parent, &MainWindow::beginClicked);
//        connect(beginButton, &QPushButton::clicked, this, &PageWelcome::test);
        // 中间组件布局
        wlay->addWidget(iconLabel, 1, Qt::AlignCenter);
        wlay->addWidget(titleLabel, 1, Qt::AlignCenter);
        wlay->addWidget(beginButton, 1, Qt::AlignCenter);
        wid->setLayout(wlay);
    // 下边缘
    QLabel *lab3 = new QLabel(this);
    lab3->setStyleSheet("QLabel{background:#3f3f3f;}");
    // 大布局添加
    vlay->addWidget(lab1, 1);
    vlay->addWidget(wid, 6);
    vlay->addWidget(lab3, 1);
    setLayout(vlay);

}

PageWelcome::~PageWelcome()
{
    delete ui;
}

void PageWelcome::test()
{
    qDebug() << "????";
}
