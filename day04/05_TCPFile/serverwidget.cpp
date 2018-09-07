#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget),
    tcpServer(nullptr),
    tcpSocket(nullptr)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);

    tcpServer->listen(QHostAddress(QHostAddress::Any),8888);
    setWindowTitle("Server port:8888");

    ui->selectButton->setEnabled(false);
    ui->sendButton->setEnabled(false);

    connect(tcpServer, &QTcpServer::newConnection,
            [=](){
                tcpSocket = tcpServer->nextPendingConnection();
                //获取套接字IP以及端口
                QString ip = tcpSocket->peerAddress().toString();
                auto port = tcpSocket->peerPort();
                QString temp = QString("[%1:%2]: connect successfully!").arg(ip).arg(port);
                this->setWindowTitle(QString("Connected from:[%1:%2]").arg(ip).arg(port));
                this->ui->textEdit->setText(temp);

                this->ui->selectButton->setEnabled(true);

                //连接之后才能读写
//                connect(this->tcpSocket, &QTcpSocket::readyRead,
//                        [=](){
//                            QByteArray arr = tcpSocket->readAll();
//                            this->ui->ReadEdit->append(QString(arr));
//                        }
//                );

                connect(this->tcpSocket, &QTcpSocket::disconnected,
                        [=](){
                            this->tcpSocket->close();
                            this->tcpSocket = nullptr;
                            this->setWindowTitle("Server");
                        }
                );

                connect(&this->myTimer,&QTimer::timeout,
                        [=](){
                            myTimer.stop();

                            sendData();
                        }
                );

            }
    );
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_selectButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "open" , "../");
    if(false == filePath.isEmpty()){
        fileName.clear();
        fileSize = 0;
        sendSize = 0;

        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();

        file.setFileName(filePath);

        bool isOk = file.open(QIODevice::ReadOnly);
        if(false == isOk){
            qDebug()<<"Open fail!";
        }else{
            this->ui->textEdit->append(QString("Send file selected:%1").arg(fileName));
            this->ui->sendButton->setEnabled(true);
            this->ui->selectButton->setEnabled(false);

        }

    }else{
        qDebug()<<"Wrong file path!";
    }

}

void ServerWidget::on_sendButton_clicked()
{
    //先发送文件头部信息
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    //发送头部信息
    qint64 len = this->tcpSocket->write(head.toUtf8());
    if(len>0){//头部发送成功
        //防止TCP黏包，定时器延时20ms
        myTimer.start(50);

    }else{
        qDebug()<<"file head send fail";
        this->file.close();
        this->ui->selectButton->setEnabled(true);
        this->ui->sendButton->setEnabled(false);
    }



}


void ServerWidget::sendData(){
    qint64 len = 0;
    char buff[1024*4] = {0};
    while(1){
        len = file.read(buff,sizeof(buff));
        if(len == 0) break;
        qint64 temp = len;
        char * pos = buff;
        while(temp > 0){
            qint64 s = this->tcpSocket->write(pos,temp);
            temp -= s;
            pos += s;
        }

        this->sendSize += len;
    }

    if(sendSize == fileSize){
        this->ui->textEdit->append("Send file successfully");
        this->file.close();

        this->tcpSocket->disconnectFromHost();
        this->tcpSocket->close();

    }

}


