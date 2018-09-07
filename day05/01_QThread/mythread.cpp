#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

void MyThread::run(){
    //数据处理，耗时5s
    QThread::sleep(5);

    emit isDone();
}
