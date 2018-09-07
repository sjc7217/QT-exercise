#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    myT = new MyThread;

    thread = new QThread(this);

    myT->moveToThread(thread);

    thread->start();

    connect(ui->pushButton, &QPushButton::clicked, myT,&MyThread::drawImage);
    connect(myT,&MyThread::updateImage, this, &Widget::getImage);
    connect(this,&Widget::destroyed,this,&Widget::closeDeal);

}

void Widget::closeDeal(){
    thread->quit();
    thread->wait();
    delete myT;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent *e){
    QPainter p(this);
    p.drawImage(50,50,image);
}

void Widget::getImage(QImage temp){
    image = temp;
    update();
}
