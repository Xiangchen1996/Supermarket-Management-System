#include "employeedialog.h"
#include "ui_employeedialog.h"
#include <timethread.h>
#include <umethod.h>
#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>

//extern QString uni_id;
//extern QString uni_pwd;
extern TimeThread *time;
extern UMethod *tools;

employeeDialog::employeeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employeeDialog)
{

    ui->setupUi(this);
//    ui->name->setText(uni_id);
//    ui->time->setText(UMethod::getCurrentTime());
    ui->tabWidget->setCurrentIndex(0);
    widgetDisable();
    tools->reset();
    connect(tools->client, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(time, SIGNAL(timeReady()), this, SLOT(getTime()));
    parser=new JsonParser();
    wrapper=new JsonWrapper();
}

employeeDialog::~employeeDialog()
{
    delete ui;
}

void employeeDialog:: getTime(){
    //ui->time->setText(UMethod::getCurrentTime());
}

void employeeDialog::on_search_submit_clicked()
{
    searchPerson(ui->search_name->text());
}

void employeeDialog::searchPerson(QString name)
{
    tools->sendMessage(wrapper->wrapSearchPerson(name));
}
void employeeDialog::createPerson(QString info){

    tools->sendMessage(info);

}


void employeeDialog::readMessage()
{
    QString readString=tools->readMessage();
    parser->setMessage(readString);
    QString res=parser->getResult();
    switch(currentIndex){

    case 0:

        if(res.startsWith("error")||res.startsWith("success")){
            QMessageBox::information(this, tr("From Server"),res);
        }else{
            ui->s_pwd->setText(parser->getPassword());
            ui->s_name->setText(parser->getName());
            ui->s_sex->setText(parser->getSex());
            ui->s_IDnum->setText(parser->getIDNumber());
            ui->s_add->setText(parser->getAddress());
            ui->s_phone->setText(parser->getPhone());
            if(0!=parser->getAdmin()){
                ui->s_admin->setChecked(true);
            }else{
                ui->s_admin->setChecked(false);
            }
        }

        break;
    case 1:
        QMessageBox::information(this, tr("From Server"),res);
        break;
    case 2:if(res.startsWith("error")||res.startsWith("success")){
            QMessageBox::information(this, tr("From Server"),res);
        }else{
            ui->delete_name->setText(parser->getName());
        }
        break;
    case 3:if(res.startsWith("error")||res.startsWith("success")){
            QMessageBox::information(this, tr("From Server"),res);
            ui->update_clear->click();
            widgetDisable();
        }else{
            ui->update_pwd->setText(parser->getPassword());
            ui->update_name->setText(parser->getName());
            ui->update_sex->setText(parser->getSex());
            ui->update_add->setText(parser->getAddress());
            ui->update_phone->setText(parser->getPhone());
            ui->update_IDnum->setText(parser->getIDNumber());
            if(0!=parser->getAdmin()){
                ui->update_admin->setChecked(true);
            }else{
                ui->update_admin->setChecked(false);
            }
            widgetEnable();
        }
        break;

    }

}

void employeeDialog::widgetEnable()
{
    ui->update_add->setEnabled(true);
    ui->update_admin->setEnabled(true);
    ui->update_IDnum->setEnabled(true);
    ui->update_add->setEnabled(true);
    ui->update_name->setEnabled(true);
    ui->update_phone->setEnabled(true);
    ui->update_pwd->setEnabled(true);
    ui->update_sex->setEnabled(true);

}

void employeeDialog::widgetDisable()
{

    ui->update_add->setDisabled(true);
    ui->update_admin->setDisabled(true);
    ui->update_IDnum->setDisabled(true);
    ui->update_add->setDisabled(true);
    ui->update_name->setDisabled(true);
    ui->update_phone->setDisabled(true);
    ui->update_pwd->setDisabled(true);
    ui->update_sex->setDisabled(true);
}


void employeeDialog::on_clear_clicked()
{
    ui->c_add->setText("");
    ui->c_id->setText("");
    ui->c_IDnum->setText("");
    ui->c_phone->setText("");
    ui->c_sex->setText("");
    ui->c_name->setText("");
    ui->c_pwd->setText("");
    ui->c_admin->setChecked(false);

}

void employeeDialog::on_addPerson_clicked()
{
    if(NULL==ui->c_add->text()||NULL==ui->c_id->text()||NULL==ui->c_IDnum->text()||NULL==ui->c_phone->text()
            ||NULL==ui->c_sex->text()||NULL==ui->c_name->text()||NULL==ui->c_pwd){
        QMessageBox::information(this, tr("Client"),tr("donot leave blank"));


    }else{
        int admin=0;
        if(ui->c_admin->isChecked()){
            admin=1;
        }
        QString command;
        command=wrapper->wrapSignUpPerson(ui->c_id->text(),ui->c_pwd->text(),admin,ui->c_name->text(),ui->c_sex->text(),ui->c_add->text(),
                                          ui->c_phone->text(),ui->c_IDnum->text());
        createPerson(command);
    }
}

void employeeDialog::on_request_name_clicked()
{
    searchPerson(ui->delete_id->text());

}

void employeeDialog::on_tabWidget_currentChanged(int index)
{
    currentIndex=index;
}

void employeeDialog::on_submit_delete_clicked()
{
    deletePerson(wrapper->wrapDeletePerson(ui->delete_id->text()));
}

void employeeDialog::deletePerson(QString info)
{
    tools->sendMessage(info);
}

void employeeDialog::on_update_info_clicked()
{
    searchPerson(ui->update_id->text());
}

void employeeDialog::on_update_clear_clicked()
{
    ui->update_add->setText("");
    ui->update_admin->setChecked(false);
    ui->update_id->setText("");
    ui->update_IDnum->setText("");
    ui->update_name->setText("");
    ui->update_phone->setText("");
    ui->update_pwd->setText("");
    ui->update_sex->setText("");
}

void employeeDialog::on_submit_update_clicked()
{
    if(NULL==ui->update_add->text()||NULL==ui->update_IDnum||NULL==ui->update_name||NULL==ui->update_phone||
            NULL==ui->c_pwd||NULL==ui->c_sex){
        QMessageBox::information(this, tr("Client"),tr("donot leave blank"));
    }else{
        int admin=0;
        if(ui->update_admin->isChecked()){
            admin=1;
        }
        QString command;
        command=wrapper->wrapUpdatePerson(ui->update_id->text(),ui->update_pwd->text(),admin,ui->update_name->text(),ui->update_sex->text()
                                          ,ui->update_add->text(),ui->update_phone->text(),ui->update_IDnum->text());
        updatePerson(command);
    }
}

void employeeDialog::updatePerson(QString info)
{
    tools->sendMessage(info);
}
