#include "logindialog.h"
#include "ui_logindialog.h"
#include <QLineEdit>
#include <QMouseEvent>
#include <umethod.h>
#include <maindialog.h>
#include <jsonwrapper.h>

extern UMethod *tools;
extern QString uni_id;
extern QString uni_pwd;
extern int admin;
extern JsonWrapper *wrapper;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    ui->pwd->setEchoMode(QLineEdit::Password);
    //下面两行设置LineEdit无边框
    ui->id->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
    ui->pwd->setStyleSheet("QLineEdit{border-width:0;border-style:outset}");
//    ui->min->setEnabled(true);
//    ui->close->setEnabled(true);
//    ui->login->setEnabled(true);

    id_edit=ui->id;
    pwd_edit=ui->pwd;

    parser=new JsonParser();
    tools->reset();
    connect(tools->client, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tools->client, SIGNAL(error(QAbstractSocket::SocketError)),
        this, SLOT(displayError(QAbstractSocket::SocketError)));

}

Widget::~Widget()
{
    delete ui;

}




void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(mousepressd && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos()- mousePoint);
        e->accept();
    }

}


void Widget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mousepressd = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *){
    mousepressd = false;
}

void Widget::keyPressEvent(QKeyEvent *e)
{

    switch(e->key()){
    case Qt::Key_Enter:
        ui->login->click();
        break;
    case Qt::Key_Return:
        ui->login->click();
        break;
    case Qt::Key_Escape:
        ui->close->click();
        break;
    }
}





void Widget::login()
{
    sendMessage();

}

void Widget::sendMessage()
{
    QString sendString;
    QString uid=id_edit->text();
    QString pwd=pwd_edit->text();
    if(NULL==uid||NULL==pwd){
        QMessageBox::information(this, tr("Market Client"),
            tr("Please input the rigth format id and password"));
        return;
    }

    QString md5_id;
    QString md5_pwd;

    md5_id=UMethod::MD5encrypt(uid);
    md5_pwd=UMethod::MD5encrypt(pwd);


    sendString=wrapper->wrapLogin(md5_id,md5_pwd);

    tools->sendMessage(sendString);



}


void Widget::readMessage()
{
    QString readString=tools->readMessage();
    if(NULL==readString){
        return;
    }
    parser->setMessage(readString);
    QString res=parser->getResult();
    int flag=parser->getAdmin();
    QString ad="success";
    if(2==flag){
        ad="success super admin";
    }else if(1==flag){
        ad="success admin";
    }else{
        ad="success";
    }
    if(res.startsWith("success")){
        QMessageBox::information(this, tr("Market Client"),
            ad);

        uni_id=id_edit->text();
        uni_pwd=pwd_edit->text();

        admin=flag;

        this->close();
        mainDialog *main=new mainDialog();
        main->exec();
    }else{
        QMessageBox::information(this, tr("Market Client"),
            readString);
    }
}


void Widget::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
            tr("The host was not found. Please check the "
            "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
            tr("The connection was refused by the peer. "
            "Make sure the fortune server is running, "
            "and check that the host name and port "
            "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
            tr("The following error occurred: %1.")
            .arg(tools->client->errorString()));
    }
}

void Widget::on_close_clicked()
{
    this->close();
}

void Widget::on_min_clicked()
{
    this->showMinimized();
}

void Widget::on_login_clicked()
{
    //验证

    login();
}

