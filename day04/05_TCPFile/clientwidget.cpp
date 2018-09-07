#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    this->isStart = true;
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::readyRead,
            [=](){
                //取出接收的内容
                QByteArray buff = tcpSocket->readAll();

                if(isStart == true){//第一次传输包含文件信息
                    isStart = false;
                    fileName = QString(buff).section("##",0,0);
                    fileSize = QString(buff).section("##",1,1).toInt();
                    recvSize = 0;

                    file.setFileName(fileName);

                    bool isOk = file.open(QIODevice::WriteOnly);
                    if( isOk == false ){
                        qDebug()<<"open file fail";
                    }

                }else{
                    qint64 len = file.write(buff);
                    recvSize += len;
                    if(recvSize == fileSize){
                        file.close();
                        QMessageBox::information(this,"Receive file complete","Receive file complete");

                        tcpSocket->disconnectFromHost();
                        tcpSocket->close();
                    }

                }
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
    QString ip = this->ui->IPEdit->text();
    auto port = this->ui->portEdit->text().toInt();

    //主动和服务器建立连接
    this->tcpSocket->connectToHost(QHostAddress(ip), port);
}
