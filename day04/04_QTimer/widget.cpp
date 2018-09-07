#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    myTimer(nullptr)
{
    ui->setupUi(this);

    this->myTimer = new QTimer(this);

    connect(myTimer, &QTimer::timeout,
            [=](){
                static int i = 0;
                i++;
                this->ui->lcdNumber->display(i);
            }
    );


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startButton_clicked()
{
    //启动定时器
    //时间间隔为100ms
    //每隔100ms，定时器myTimer自动触发timeout信号
    if(myTimer->isActive() == false)
        this->myTimer->start(100);

}

void Widget::on_stopButton_clicked()
{
    if(myTimer->isActive())
        this->myTimer->stop();
}
