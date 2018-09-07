#include<QApplication>
#include<QWidget>
#include<QPushButton>

int main(int argc,char **argv){
    QApplication app(argc,argv);

    QWidget w;
    w.setWindowTitle("ddddd");
    w.show();

    QPushButton q(&w);
    q.setText(QString("uwegfbv"));
    //q.setParent(&w);
    q.show();

    app.exec();

    return 0;
}
