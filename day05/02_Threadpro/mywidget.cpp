#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //自定义线程，继承自QObject
    thread = new MyThread();

    //创建子线程
    qthread = new QThread(this);

    //把自定义线程加入到子线程中
    thread->moveToThread(qthread);  //将线程类与自定义任务类结合起来

    connect(thread, &MyThread::mySignal, this, &MyWidget::dealSignal);

    connect(this, &MyWidget::startThread,thread, &MyThread::myTimeout);//主进程发送信号使得子进程调用线程函数

    connect(this, &MyWidget::destroyed, this, &MyWidget::dealClose);    //窗口关闭时关闭子线程

    qDebug()<<"ID of main process is:"<<QThread::currentThread();
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::dealSignal(){
    static int i = 0;
    ++i;
    ui->lcdNumber->display(i);
}

void MyWidget::on_startButton_clicked()
{
    if(qthread->isRunning() == true) return;
    qthread->start();
    thread->setFlag();

    emit startThread();

}

void MyWidget::on_stopButton_clicked()
{
    //thread->

    if(qthread->isRunning() == false) return;

    thread->setFlag(false);
    qthread->quit();
    qthread->wait();
}


void MyWidget::dealClose(){
    if(qthread->isRunning() == false) return;

    thread->setFlag(false);
    qthread->quit();
    qthread->wait();
}
