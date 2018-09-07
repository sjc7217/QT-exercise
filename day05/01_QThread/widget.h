#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "mythread.h"
#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void dealTimeout();
    void dealDone();//线程结束处理函数
    void stopThread();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QTimer * myTimer;

    MyThread *thread;
};

#endif // WIDGET_H
