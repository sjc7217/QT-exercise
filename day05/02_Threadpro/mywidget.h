#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "mythread.h"
#include<QDebug>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

private slots:
    void on_startButton_clicked();
    void dealSignal();
    void dealClose();

    void on_stopButton_clicked();

signals:
    void startThread();
private:
    Ui::MyWidget *ui;
    MyThread * thread;//自定义线程类用来定义线程操作函数
    QThread * qthread;//QThread用来驱动新线程

};

#endif // MYWIDGET_H
