#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //打印Qt支持的数据库驱动
    //qDebug()<<QSqlDatabase::drivers();

    //添加MySql数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("312362");
    db.setDatabaseName("world");

    //打开数据库
    if(true != db.open()){
        QMessageBox::warning(this,"Error",db.lastError().text());
        return;
    }

//    QSqlQuery query;
//    query.exec("select * from city limit 10;");

//    while(query.next()){
//        qDebug()<< query.value(0).toInt() <<query.value(1).toString();
//    }
    //设置模型
    model = new QSqlTableModel(this);
    model->setTable("city");

    //把model放在view里面
    ui->tableView->setModel(model);
    //显示model里面的数据
    model->select();

    //设置标题行
    model->setHeaderData(0,Qt::Horizontal,"序号");

    //设置手动提交模式
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置是否能修改
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_addButton_clicked()
{
    //添加空记录
    QSqlRecord record = model->record();
    //获取行号
    int row = model->rowCount();
    model->insertRecord(row, record);
}

void Widget::on_confirmButton_3_clicked()
{
    //手动确认提交
    model->submitAll();
}

void Widget::on_deleteButton_2_clicked()
{
    //获取选中的模型
    auto smodel = ui->tableView->selectionModel();
    //取出模型中的索引
    auto list = smodel->selectedRows();
    //删除所有选中的行
    for(int i = 0;i < list.size(); ++i){
        model->removeRow(list.at(i).row());
    }

}

void Widget::on_cancelButton_4_clicked()
{
    //回滚，恢复
    model->revertAll();
    model->submitAll();
}

void Widget::on_searchButton_5_clicked()
{
    auto name = ui->lineEdit->text();

    auto str = QString("Name='%1'").arg(name);
    model->setFilter(str);
    model->select();

}
