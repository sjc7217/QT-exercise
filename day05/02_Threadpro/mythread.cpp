#include "mythread.h"

MyThread::MyThread(QObject *parent) : QObject(parent)
{
    isStop = true;
}


void MyThread::myTimeout(){
    while(1){
        if(isStop == false) break;
        QThread::sleep(1);
        emit mySignal();
        qDebug()<<"ID of child process is:"<<QThread::currentThread();
    }

}



