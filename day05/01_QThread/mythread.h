#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

signals:
    void isDone();
protected:
    //QThread虚函数，线程处理函数
    //不能直接调用，通过start间接调用
    void run();
public slots:
};

#endif // MYTHREAD_H
