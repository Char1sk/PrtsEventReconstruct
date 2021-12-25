#ifndef PAGEWELCOME_H
#define PAGEWELCOME_H

#include <QWidget>
#include <QLabel>
#include <QIcon>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class PageWelcome;
}

class PageWelcome : public QWidget
{
    Q_OBJECT

public:
    explicit PageWelcome(QWidget *parent = 0);
    ~PageWelcome();
    QPushButton *beginButton;

public slots:
    void test();

private:
    Ui::PageWelcome *ui;
};

#endif // PAGEWELCOME_H
