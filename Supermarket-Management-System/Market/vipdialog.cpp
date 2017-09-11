#include "vipdialog.h"
#include "ui_vipdialog.h"
#include <umethod.h>
#include <timethread.h>
#include <QMessageBox>

//extern QString uni_id;
//extern QString uni_pwd;
extern UMethod *tools;
extern TimeThread *time;
vipDialog::vipDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vipDialog)
{
    ui->setupUi(this);
    tools->reset();
    parser=new JsonParser();
    wrapper=new JsonWrapper();

//    ui->name->setText(uni_id);
//    ui->time->setText(UMethod::getCurrentTime());

    connect(time,SIGNAL(timeReady()),this,SLOT(getTime()));
    connect(tools->client, SIGNAL(readyRead()), this, SLOT(readMessage()));
    currentIndex=ui->tabWidget->currentIndex();
}

vipDialog::~vipDialog()
{
    delete ui;
}

void vipDialog::getTime()
{
   // ui->time->setText(UMethod::getCurrentTime());
}

void vipDialog::readMessage()
{
    QString readString=tools->readMessage();
    parser->setMessage(readString);
    QString res=parser->getResult();
    //QMessageBox::information(this, tr("Fortune Client"),res);
    switch(currentIndex){
    case 0:
        if(res.startsWith("true")){
            ui->search_vip_score->setText(QString::number(parser->getScore()));
            ui->search_vip_name->setText(parser->getName());
        }else{
            QMessageBox::information(this, tr("Fortune Client"),res);
        }
        break;
    case 1:QMessageBox::information(this, tr("Fortune Client"),res);
        break;
    case 2:
        if(res.startsWith("true")){
            ui->delete_vip_score->setText(QString::number(parser->getScore()));
            ui->delete_vip_name->setText(parser->getName());
        }else{
            QMessageBox::information(this, tr("Fortune Client"),res);
        }
        break;
    case 3:QMessageBox::information(this, tr("Fortune Client"),res);
        break;

    }

}

void vipDialog::on_search_vip_submit_clicked()
{
    if(0!=ui->search_vip_id->text().compare("")){
        QString command=wrapper->wrapSearchVIP(ui->search_vip_id->text().toUpper());
        tools->sendMessage(command);
    }else{
        QMessageBox::information(this, tr("Fortune Client"),"please input right info");
    }
}

void vipDialog::on_tabWidget_currentChanged(int index)
{
    currentIndex=index;
}

void vipDialog::on_clear_clicked()
{
    ui->create_vip_id->setText("");
    ui->create_vip_name->setText("");
    ui->create_vip_phone->setText("");
}

void vipDialog::on_addPerson_clicked()
{
    if(0!=ui->create_vip_id->text().compare("")&&0!=ui->create_vip_name->text().compare("")&&0!=ui->create_vip_phone->text().compare(""))
    {
        QString command=wrapper->wrapCreateVIP(ui->create_vip_id->text().toUpper(),ui->create_vip_name->text(),ui->create_vip_phone->text());
        tools->sendMessage(command);
    }else{
        QMessageBox::information(this, tr("Fortune Client"),"please input right info");
    }
}

void vipDialog::on_request_info_clicked()
{
    if(0!=ui->delete_vip_id->text().compare("")){
        QString command=wrapper->wrapSearchVIP(ui->delete_vip_id->text().toUpper());
        tools->sendMessage(command);
    }else{
        QMessageBox::information(this, tr("Fortune Client"),"please input right info");
    }
}

void vipDialog::on_submit_delete_clicked()
{
    if(0!=ui->delete_vip_id->text().compare("")&&0!=ui->delete_vip_name->text().compare("")&&0!=ui->delete_vip_score->text().compare(""))
    {
        QString command=wrapper->wrapDeleteVIP(ui->delete_vip_id->text().toUpper());
        tools->sendMessage(command);
    }else{
        QMessageBox::information(this, tr("Fortune Client"),"please input right info");
    }
}

void vipDialog::on_update_clear_clicked()
{
    ui->update_vip_id->setText("");
    ui->update_vip_score->setText("");
}

void vipDialog::on_submit_update_clicked()
{
    if(0!=ui->update_vip_score->text().compare("")&&0!=ui->update_vip_id->text().compare(""))
    {
        QString command=wrapper->wrapExchangeVIP(ui->update_vip_id->text().toUpper(),ui->update_vip_score->text().toInt());
        tools->sendMessage(command);
    }else{
        QMessageBox::information(this, tr("Fortune Client"),"please input right info");
    }
}
