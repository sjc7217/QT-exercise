#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    void myTimeout();
    void setFlag(bool i = true){
        isStop = i;
    }



signals:
    void mySignal();

public slots:


private:
    bool isStop;
};

#endif // MYTHREAD_H
