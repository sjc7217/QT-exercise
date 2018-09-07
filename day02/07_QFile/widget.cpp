#include "widget.h"
#include "ui_widget.h"
#include<QFile>
#include<QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_ReadButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"open","../","TXT(*.txt)");
    if(path.isEmpty() == false){

    }
}
