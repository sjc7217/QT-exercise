#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    udpSocket(nullptr)
{
    ui->setupUi(this);
    //分配内存空间并绑定父对象
    udpSocket = new QUdpSocket(this);

    //绑定
    udpSocket->bind(8888);

    setWindowTitle("服务器端口：8888");

    //当对方成功发送过来
    //触发槽函数
    connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::dealMsg);

}

void Widget::dealMsg(){
    char buff[1024] = {0};
    QHostAddress cliAddr;
    quint16 port;
    qint64 len = udpSocket->readDatagram(buff, sizeof(buff),&cliAddr,&port);

    if(len>0){
        QString str = QString("[%1:%2] %3").arg(cliAddr.toString()).arg(port).arg(buff);
        ui->textEdit->setText(str);
    }
}


Widget::~Widget()
{
    delete ui;
}

void Widget::on_sendButton_clicked()
{
    //先获取对方IP和端口
    QString ip = this->ui->IPEdit->text();
    quint16 port = this->ui->portEdit->text().toInt();

    //获取编辑区内容
    QString str = this->ui->textEdit->toPlainText();

    //发送数据
    udpSocket->writeDatagram(str.toUtf8(),QHostAddress(ip),port);
}

void Widget::on_closeButton_clicked()
{

}
