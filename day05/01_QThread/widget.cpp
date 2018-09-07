#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);

    //只要定时器启动，自动触发timeout信号
    connect(myTimer, &QTimer::timeout, this, &Widget::dealTimeout);

    thread = new MyThread(this);

    connect(thread, &MyThread::isDone, this, &Widget::dealDone);


    connect(this, &Widget::destroyed, this, &Widget::stopThread);
}

void Widget::stopThread(){
    thread->quit();
    thread->wait();
}

void Widget::dealDone(){
    qDebug()<<"Over";
    myTimer->stop();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::dealTimeout(){
    static int i = 0;
    i++;
    this->ui->lcdNumber->display(i);
}

void Widget::on_pushButton_clicked()
{
    if(myTimer->isActive() == false)
        this->myTimer->start(100);

//    QThread::sleep(5);
    thread->start();
}
