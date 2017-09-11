#include "storagedialog.h"
#include "ui_storagedialog.h"
#include <QStandardItemModel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <umethod.h>
#include <timethread.h>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

//extern QString uni_id;
//extern QString uni_pwd;
extern TimeThread *time;
extern UMethod *tools;

storageDialog::storageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::storageDialog)
{
    ui->setupUi(this);
//    ui->l_name->setText(uni_id);
//    ui->l_time->setText(UMethod::getCurrentTime());
    ui->tabWidget->setCurrentIndex(0);
    tools->reset();
    connect(tools->client, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(time, SIGNAL(timeReady()), this, SLOT(getTime()));

    wrapper=new JsonWrapper();
    parser=new JsonParser();

}

void storageDialog::getTime()
{
 //   ui->l_time->setText(UMethod::getCurrentTime());
}

void storageDialog::readMessage()
{
    QString readString=tools->readMessage();
    parser->setMessage(readString);
    QString res=parser->getResult();
    QJsonArray array = parser->getItemList();
    JsonParser *temp=new JsonParser();

    if(array.size()>0){
        QJsonValue ob=array.at(0);
        if(ob.isObject())
        {
             QJsonObject obj=ob.toObject();
             QJsonDocument document;
             document.setObject(obj);
             QByteArray simpbyte_array = document.toJson(QJsonDocument::Compact);
             QString str(simpbyte_array);
             temp->setMessage(str);
        }else{
             temp->setMessage("");
        }
    }else{
        temp->setMessage("");
    }

    switch(currentIndex){
    case 0:
        if(0==temp->getName().compare("")){
            QMessageBox::information(this, tr("Market Client"),tr("No record"));
        }else{
            ui->info_name->setText(temp->getName());
            ui->info_price->setText(QString::number(temp->getPrice()));
            ui->info_sup->setText(temp->getSupplier());
        }
        break;
    case 1:if(res.startsWith("success")||res.startsWith("error")){
                QMessageBox::information(this, tr("Market Client"),res);
                ui->update_clear->click();
           }
           else if(0==temp->getName().compare("")){
                QMessageBox::information(this, tr("Market Client"),tr("No record"));
           }else{
                ui->update_name->setText(temp->getName());
                ui->update_price->setText(QString::number(temp->getPrice()));
           }
        break;
    case 2:
        if(0==temp->getName().compare("")){
            QMessageBox::information(this, tr("Market Client"),tr("No record"));
        }else{
            ui->storage_name->setText(temp->getName());
            ui->storage_lastin->setText(temp->getLastIn());
            ui->storage_qty->setText(QString::number(temp->getQuantity()));
        }
        break;
    case 3:
        if(res.startsWith("success")||res.startsWith("error")){
                        QMessageBox::information(this, tr("Market Client"),res);
                        ui->update_storage_clear->click();
        }
        else if(0==temp->getName().compare("")){
            QMessageBox::information(this, tr("Market Client"),tr("No record"));
        }else{
            ui->update_storage_name->setText(temp->getName());
            ui->update_storage_qty->setText(QString::number(temp->getQuantity()));
        }
        break;
    }
}

storageDialog::~storageDialog()
{
    delete ui;
}


void storageDialog::on_info_submit_clicked()
{
    if(NULL==ui->info_code->text()){
        QMessageBox::information(this, tr("Market Client"),tr("Please input the rigth code"));
    }else{
        QString s_id=ui->info_code->text().toUpper();
        QString command=wrapper->wrapSearchItemById(s_id);
        itemInfo(command);
    }
}


void storageDialog::itemInfo(QString info)
{
    tools->sendMessage(info);
}

void storageDialog::on_tabWidget_currentChanged(int index)
{
    currentIndex=index;
}

void storageDialog::on_storage_submit_clicked()
{
    if(NULL==ui->storage_code->text()){
        QMessageBox::information(this, tr("Market Client"),tr("Please input the rigth code"));
    }else{
        QString s_id=ui->storage_code->text().toUpper();
        QString command=wrapper->wrapSearchItemById(s_id);
        storageInfo(command);
    }
}

void storageDialog::storageInfo(QString info)
{
    tools->sendMessage(info);
}

void storageDialog::on_update_clear_clicked()
{
    ui->update_name->setText("");
    ui->update_code->setText("");
    ui->update_price->setText("");
}

void storageDialog::on_update_request_clicked()
{
    if(NULL==ui->update_code->text()){
        QMessageBox::information(this, tr("Market Client"),tr("Please input the rigth code"));
    }else{
        QString s_id=ui->update_code->text().toUpper();
        QString command=wrapper->wrapSearchItemById(s_id);
        itemInfo(command);
    }
}

void storageDialog::on_update_submit_clicked()
{
    if(NULL==ui->update_code->text()||NULL==ui->update_name->text()||NULL==ui->update_price->text()){
        QMessageBox::information(this, tr("Market Client"),tr("Please input the rigth info"));
    }else{
        QString s_id=ui->update_code->text().toUpper();
        QString command=wrapper->wrapUpdateItemInfo(s_id,ui->update_name->text(),ui->update_price->text().toDouble());
        updateInfo(command);
    }
}

void storageDialog::on_update_storage_request_clicked()
{
    if(NULL==ui->update_storage_code->text()){
        QMessageBox::information(this, tr("Market Client"),tr("Please input the rigth code"));
    }else{
        QString s_id=ui->update_storage_code->text().toUpper();
        QString command=wrapper->wrapSearchItemById(s_id);
        updateStorage(command);
    }
}

void storageDialog::on_update_storage_clear_clicked()
{
    ui->update_storage_code->setText("");
    ui->update_storage_name->setText("");
    ui->update_storage_qty->setText("");
}

void storageDialog::on_update_storage_submit_clicked()
{
    if(NULL==ui->update_storage_code->text()||NULL==ui->update_storage_name->text()||NULL==ui->update_storage_qty->text()){
        QMessageBox::information(this, tr("Market Client"),tr("Please input the rigth info"));
    }else{
        QString s_id=ui->update_storage_code->text().toUpper();
        QString command=wrapper->wrapUpdateStorageInfo(s_id,ui->update_storage_name->text(),ui->update_storage_qty->text().toInt());
        updateStorage(command);
    }
}

void storageDialog::updateInfo(QString info)
{
    tools->sendMessage(info);
}

void storageDialog::updateStorage(QString info)
{
    tools->sendMessage(info);
}
