#include "mythread.h"

MyThread::MyThread(QObject *parent) : QObject(parent)
{

}


void MyThread::drawImage(){
    //定义QImage绘图设备
    QImage image(500,500,QImage::Format_ARGB32);
    //定义画家
    QPainter p(&image);

    //定义5个点
    QPoint a[5];
    for(int i=0;i<5;++i) a[i] = QPoint(qrand()%500,qrand()%500);

    QPen pen;//设置画笔
    pen.setWidth(5);//设置宽度
    p.setPen(pen);

    QBrush brush;//设置笔的样式
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    p.setBrush(brush);

    p.drawPolygon(a,5);

    //信号传参
    emit updateImage(image);

}
