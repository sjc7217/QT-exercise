#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include "mythread.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void paintEvent(QPaintEvent *e);
    void getImage(QImage temp);
    void closeDeal();
private:
    Ui::Widget *ui;
    QImage image;
    MyThread * myT;
    QThread * thread;
};

#endif // WIDGET_H
