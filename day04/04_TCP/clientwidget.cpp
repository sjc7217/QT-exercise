#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>


ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget),
    tcpSocket(nullptr)
{
    this->ui->setupUi(this);

    this->setWindowTitle("Client");
    //分配空间，指定父对象
    this->tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::connected,
            [=](){

                QString ip = tcpSocket->peerAddress().toString();
                auto port = tcpSocket->peerPort();
                QString temp = QString("[%1:%2]:连接成功").arg(ip).arg(port);

                this->ui->ReadEdit->setText(temp);
                //获取套接字IP以及端口
                this->setWindowTitle(QString("已连接到:[%1:%2]").arg(ip).arg(port));
            }


    );

    connect(tcpSocket,&QTcpSocket::readyRead,
            [=](){
                //获取套接字中所有数据
                QByteArray arr = this->tcpSocket->readAll();
                //写入窗口
                this->ui->ReadEdit->append(QString(arr));
            }
    );

    connect(this->tcpSocket, &QTcpSocket::disconnected,
            [=](){
                this->tcpSocket->close();
                this->tcpSocket = nullptr;
                this->setWindowTitle("Client");
            }
    );

}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_connectButton_clicked()
{
    //获取ip以及端口号
    QString ip = this->ui->serverIP->text();
    auto port = this->ui->serverport->text().toInt();

    //主动和服务器建立连接
    this->tcpSocket->connectToHost(QHostAddress(ip), port);
}

void ClientWidget::on_sendButton_clicked()
{
    //获取编辑框内容
    QString str = this->ui->WriteEdit->toPlainText();
    //发送数据
    this->tcpSocket->write(str.toUtf8());
}

void ClientWidget::on_closeButton_clicked()
{
    this->tcpSocket->disconnectFromHost();
    this->tcpSocket->close();
    this->setWindowTitle("Client");
}
