#include "providerdialog.h"
#include "ui_providerdialog.h"
#include <QStandardItemModel>
#include <umethod.h>
#include <timethread.h>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <exportexcelobject.h>
#include <QFileDialog>

//extern QString uni_id;
//extern QString uni_pwd;
extern TimeThread *time;
extern UMethod *tools;

providerDialog::providerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::providerDialog)
{
    ui->setupUi(this);
//    ui->l_name->setText(uni_id);
//    ui->l_time->setText(UMethod::getCurrentTime());

    ui->tabWidget->setCurrentIndex(0);
    tools->reset();
    connect(tools->client, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(time, SIGNAL(timeReady()), this, SLOT(getTime()));

    parser=new JsonParser();
    wrapper=new JsonWrapper();
    updateDisable();

    model = new QStandardItemModel();
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,tr("供货商号"));
    model->setHeaderData(1,Qt::Horizontal,tr("供货商名称"));
    model->setHeaderData(2,Qt::Horizontal,tr("供货商类型"));
    model->setHeaderData(3,Qt::Horizontal,tr("联系方式"));


    ui->tableView_4->setModel(model);
    //表头信息显示居左
    ui->tableView_4->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    currentIndex=ui->tabWidget->currentIndex();
}

providerDialog::~providerDialog()
{
    delete ui;
}

void providerDialog::on_tabWidget_currentChanged(int index)
{
    currentIndex=index;
}

void providerDialog::getTime()
{
  //  ui->l_time->setText(UMethod::getCurrentTime());
}

void providerDialog::modelReset()
{
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,tr("供货商号"));
    model->setHeaderData(1,Qt::Horizontal,tr("供货商名称"));
    model->setHeaderData(2,Qt::Horizontal,tr("供货商类型"));
    model->setHeaderData(3,Qt::Horizontal,tr("联系方式"));
}

void providerDialog::readMessage()
{
    QString readString=tools->readMessage();
    parser->setMessage(readString);

    QString res=parser->getResult();
    switch(currentIndex){
    case 0:
        if(res.startsWith("error")){
            QMessageBox::information(this, tr("Market Client"),res);
        }else{
            model->clear();
            modelReset();
            QJsonArray array = parser->getSupplierList();
            for(int i=0;i<array.size();i++){
                QJsonValue ob=array.at(i);
                if(ob.isObject())
                {
                     QJsonObject obj=ob.toObject();
                     QJsonDocument document;
                     document.setObject(obj);
                     QByteArray simpbyte_array = document.toJson(QJsonDocument::Compact);
                     QString str(simpbyte_array);
                     JsonParser *temp=new JsonParser();
                     temp->setMessage(str);
                     QString tp;
                     switch(temp->getType()){
                     case 0:
                         tp="生鲜";
                         break;
                     case 1:
                         tp="百货";
                         break;
                     }

                     model->setItem(i,0,new QStandardItem(temp->getId()));
                     model->item(i,0)->setTextAlignment(Qt::AlignCenter);
                     model->setItem(i,1,new QStandardItem(temp->getName()));
                     model->item(i,1)->setTextAlignment(Qt::AlignCenter);
                     model->setItem(i,2,new QStandardItem(tp));
                     model->item(i,2)->setTextAlignment(Qt::AlignCenter);
                     model->setItem(i,3,new QStandardItem(temp->getPhone()));
                     model->item(i,3)->setTextAlignment(Qt::AlignCenter);
                }
            }
        }
        break;
    case 1:
        QMessageBox::information(this, tr("Market Client"),res);
        break;
    case 2:
        if(res.startsWith("success")||res.startsWith("error")){
            QMessageBox::information(this, tr("Market Client"),res);
        }else{
            ui->delete_sup_name->setText(parser->getName());
            QString type;
            int flag=parser->getType();
            if(0==flag){
                type="生鲜";
            }else if(1==flag)
            {
                type="百货";
            }
            ui->delete_sup_type->setText(type);
            ui->delete_sup_phone->setText(parser->getPhone());
        }
        break;
    case 3:
        if(res.startsWith("success")){
            QMessageBox::information(this, tr("Market Client"),res);
            ui->update_clear->click();
            updateDisable();
        }
        else if(res.startsWith("error")){
            QMessageBox::information(this, tr("Market Client"),res);
            ui->update_clear->click();
        }else{
            updateEnable();
            ui->update_sup_name->setText(parser->getName());
            ui->update_sup_type->setCurrentIndex(parser->getType());
            ui->update_sup_phone->setText(parser->getPhone());
        }
        break;


    }

}

void providerDialog::updateDisable()
{
    ui->update_sup_name->setDisabled(true);
    ui->update_sup_phone->setDisabled(true);
    ui->update_sup_type->setDisabled(true);
}

void providerDialog::updateEnable()
{
    ui->update_sup_name->setEnabled(true);
    ui->update_sup_phone->setEnabled(true);
    ui->update_sup_type->setEnabled(true);
}

void providerDialog::on_add_sup_type_currentIndexChanged(int index)
{
    add_type=index;
}

void providerDialog::on_update_sup_type_currentIndexChanged(int index)
{
    update_type=index;
}

void providerDialog::on_request_sup_info_clicked()
{
    QString command=wrapper->wrapSearchSupplier(ui->delete_sup_id->text().toUpper());
    tools->sendMessage(command);
}

void providerDialog::on_delete_clear_clicked()
{
    ui->delete_sup_id->setText("");
    ui->delete_sup_name->setText("");
    ui->delete_sup_phone->setText("");
    ui->delete_sup_type->setText("");
}

void providerDialog::on_delete_submit_clicked()
{
    if(0!=ui->delete_sup_id->text().compare("")&&0!=ui->delete_sup_name->text().compare("")&&0!=ui->delete_sup_phone->text().compare("")
            &&0!=ui->delete_sup_type->text().compare(""))
    {
        QString command=wrapper->wrapdeleteSupplier(ui->delete_sup_id->text().toUpper());
        tools->sendMessage(command);
    }else{
        QMessageBox::information(this, tr("Market Client"),"click show button first");
    }
}

void providerDialog::on_add_clear_clicked()
{
    ui->add_sup_id->setText("");
    ui->add_sup_name->setText("");
    ui->add_sup_phone->setText("");
    ui->add_sup_type->setCurrentIndex(0);
}

void providerDialog::on_add_submit_clicked()
{
    QString command=wrapper->wrapAddSupplier(ui->add_sup_id->text().toUpper(),ui->add_sup_name->text(),add_type,ui->add_sup_phone->text());
    tools->sendMessage(command);
}

void providerDialog::on_request_sup_info_2_clicked()
{
    QString command=wrapper->wrapSearchSupplier(ui->update_sup_id->text().toUpper());
    tools->sendMessage(command);
}

void providerDialog::on_update_clear_clicked()
{
    ui->update_sup_id->setText("");
    ui->update_sup_name->setText("");
    ui->update_sup_phone->setText("");
    ui->update_sup_type->setCurrentIndex(0);
}

void providerDialog::on_update_submit_clicked()
{
    if(0!=ui->update_sup_id->text().compare("")&&0!=ui->update_sup_name->text().compare("")&&0!=ui->update_sup_phone->text().compare(""))
    {
        QString command=wrapper->wrapUpdateSupplier(ui->update_sup_id->text().toUpper(),ui->update_sup_name->text(),update_type,ui->update_sup_phone->text());
        tools->sendMessage(command);
    }else
    {
        QMessageBox::information(this, tr("Market Client"),"click show button first");
    }
}

void providerDialog::on_search_type_currentIndexChanged(int index)
{
    search_type=index;
}

void providerDialog::on_search_submit_clicked()
{
    QString command;
    switch (search_type) {
    case 0:
        command=wrapper->wrapSearchAllSupplier();
        break;
    case 1:
        command=wrapper->wrapSearchSupplierByType(search_type-1);
        break;
    case 2:
        command=wrapper->wrapSearchSupplierByType(search_type-1);
        break;
    }
    tools->sendMessage(command);
}

void providerDialog::on_toolButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tableView_4);

    // you can change the column order and
    // choose which colum to export
    obj.addField(0, "供货商号", "char(20)");
    obj.addField(3, "联系方式", "char(20)");
    obj.addField(1, "供货商名称", "char(20)");
    obj.addField(2, "供货类型", "char(20)");

//    obj.addField(4, "colum5", "char(20)");
//    obj.addField(5, "colum6", "char(20)");
    //obj.addField(6, "colum7", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}
