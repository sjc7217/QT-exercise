#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>//监听套接字头文件
#include <QTcpSocket>//通信套接字头文件


namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();

private slots:
    void on_sendButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::ServerWidget *ui;

    QTcpServer * tcpServer;
    QTcpSocket * tcpSocket;
};

#endif // SERVERWIDGET_H
