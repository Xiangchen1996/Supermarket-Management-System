#include "systemdialog.h"
#include "ui_systemdialog.h"
#include <umethod.h>
#include <timethread.h>
#include <QMessageBox>

//extern QString uni_id;
//extern QString uni_pwd;
extern UMethod *tools;
extern TimeThread *time;
systemDialog::systemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::systemDialog)
{
    ui->setupUi(this);
    tools->reset();
    parser=new JsonParser();
    wrapper=new JsonWrapper();

//    ui->name->setText(uni_id);
//    ui->time->setText(UMethod::getCurrentTime());

    connect(time,SIGNAL(timeReady()),this,SLOT(getTime()));
    connect(tools->client, SIGNAL(readyRead()), this, SLOT(readMessage()));

}


void systemDialog::getTime()
{
//    ui->time->setText(UMethod::getCurrentTime());
}

void systemDialog::readMessage()
{
    QString readString=tools->readMessage();
    parser->setMessage(readString);
    QString res=parser->getResult();
    QMessageBox::information(this, tr("Fortune Client"),res);

}


systemDialog::~systemDialog()
{
    delete ui;
}

void systemDialog::on_backupDB_clicked()
{
    QString command=wrapper->wrapBackUpDB();
    tools->sendMessage(command);
}

void systemDialog::on_clearDB_clicked()
{
    QString command=wrapper->wrapClearDB();
    tools->sendMessage(command);
}

void systemDialog::on_loadDB_clicked()
{
    QString command=wrapper->wrapLoadDB();
    tools->sendMessage(command);
}
