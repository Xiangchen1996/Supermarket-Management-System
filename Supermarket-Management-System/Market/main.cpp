#include "logindialog.h"
#include <QApplication>
#include <QTcpSocket>
#include <maindialog.h>
#include <timethread.h>
#include <umethod.h>

//标志位 是否为管理员
int admin=0;
//全局变量tcp连接
UMethod *tools;
QString uni_id;
QString uni_pwd;
TimeThread *time;



//finished-----
//employee.cpp
//main.cpp
//maindialog.cpp
//purchasedialog.cpp
//storagedialog.cpp
//umethod.cpp
//widget.cpp

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    time=new TimeThread();
    time->start();

    tools=new UMethod();

    Widget w;
    //mainDialog w;
    w.show();
    return a.exec();
}
