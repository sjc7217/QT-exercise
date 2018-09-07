#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget),
    tcpServer(nullptr),
    tcpSocket(nullptr)
{
    this->ui->setupUi(this);

    this->setWindowTitle("Server");

    this->tcpServer = new QTcpServer(this);

    this->tcpServer->listen(QHostAddress::Any,8888);

    connect(tcpServer, &QTcpServer::newConnection,
            [=](){
                //取出建立好连接的套接字
                this->tcpSocket = tcpServer->nextPendingConnection();

                //获取套接字IP以及端口
                QString ip = tcpSocket->peerAddress().toString();
                auto port = tcpSocket->peerPort();
                QString temp = QString("[%1:%2]:连接成功").arg(ip).arg(port);
                this->setWindowTitle(QString("Connected from:[%1:%2]").arg(ip).arg(port));
                this->ui->ReadEdit->setText(temp);

                //连接之后才能读写
                connect(this->tcpSocket, &QTcpSocket::readyRead,
                        [=](){
                            QByteArray arr = tcpSocket->readAll();
                            this->ui->ReadEdit->append(QString(arr));
                        }
                );

                connect(this->tcpSocket, &QTcpSocket::disconnected,
                        [=](){
                            this->tcpSocket->close();
                            this->tcpSocket = nullptr;
                            this->setWindowTitle("Server");
                        }
                );


            }
      );


}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_sendButton_clicked()
{

    if(tcpSocket != nullptr){
        //获取编辑区内容
        QString str = ui->WriteEdit->toPlainText();
        //给对方发送数据
        this->tcpSocket->write(str.toUtf8().data());
    }

}

void ServerWidget::on_closeButton_clicked()
{
    //主动和客户端断开连接
    if(tcpSocket != nullptr){
        this->tcpSocket->disconnectFromHost();
        this->tcpSocket->close();
        this->tcpSocket = nullptr;
        this->setWindowTitle("Server");

    }
}
