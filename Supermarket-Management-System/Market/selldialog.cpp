#include "selldialog.h"
#include "ui_selldialog.h"
#include <QStandardItemModel>
#include <QLineEdit>
#include <umethod.h>
#include <timethread.h>
#include <QMessageBox>
#include <jsonparser.h>
#include <jsonwrapper.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <exportexcelobject.h>
#include <QFileDialog>

//extern QString uni_id;
//extern QString uni_pwd;
extern TimeThread *time;
extern UMethod *tools;

sellDialog::sellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sellDialog)
{
    ui->setupUi(this);
    ui->s_id->setPlaceholderText("请输入查询条件");
//    ui->l_name->setText(uni_id);
//    ui->l_time->setText(tools->getCurrentTime());

    tools->reset();
    connect(tools->client,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(time,SIGNAL(timeReady()),this,SLOT(getTime()));

    parser=new JsonParser();
    wrapper=new JsonWrapper();





    //下面是销售信息查询的tableview
    model = new QStandardItemModel();
    model->setColumnCount(6);
    model->setHeaderData(0,Qt::Horizontal,tr("商品条码"));
    model->setHeaderData(1,Qt::Horizontal,tr("商品名称"));
    model->setHeaderData(2,Qt::Horizontal,tr("数量"));
    model->setHeaderData(3,Qt::Horizontal,tr("单价"));
    model->setHeaderData(4,Qt::Horizontal,tr("供货商"));
    model->setHeaderData(5,Qt::Horizontal,tr("日期"));

    ui->tableView->setModel(model);
    //表头信息显示居左
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    //下面是销售信息写入清单的tableview
    model_2 = new QStandardItemModel();
    model_2->setColumnCount(5);
    model_2->setHeaderData(0,Qt::Horizontal,tr("商品条码"));
    model_2->setHeaderData(1,Qt::Horizontal,tr("名称"));
    model_2->setHeaderData(2,Qt::Horizontal,tr("数量"));
    model_2->setHeaderData(3,Qt::Horizontal,tr("单价"));
    model_2->setHeaderData(4,Qt::Horizontal,tr("总价"));



    ui->tableView_2->setModel(model_2);
    //表头信息显示居左
    ui->tableView_2->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    currentIndex=ui->tabWidget->currentIndex();

}


sellDialog::~sellDialog()
{
    delete ui;
}

void sellDialog::modelReset()
{
    model->setColumnCount(6);
    model->setHeaderData(0,Qt::Horizontal,tr("商品条码"));
    model->setHeaderData(1,Qt::Horizontal,tr("商品名称"));
    model->setHeaderData(2,Qt::Horizontal,tr("数量"));
    model->setHeaderData(3,Qt::Horizontal,tr("单价"));
    model->setHeaderData(4,Qt::Horizontal,tr("供货商"));
    model->setHeaderData(5,Qt::Horizontal,tr("日期"));
}

void sellDialog::getTime()
{
 //   ui->l_time->setText(UMethod::getCurrentTime());
}

void sellDialog::purchaseClear()
{
    model_2->setColumnCount(2);
    model_2->setHeaderData(0,Qt::Horizontal,tr("商品条码"));
    model_2->setHeaderData(1,Qt::Horizontal,tr("名称"));
    model_2->setHeaderData(2,Qt::Horizontal,tr("数量"));
    model_2->setHeaderData(3,Qt::Horizontal,tr("单价"));
    model_2->setHeaderData(4,Qt::Horizontal,tr("总价"));

}

void sellDialog::calculateTotalPay()
{
    sum=0;
    for(int i=0;i<model_2->rowCount();i++){
        sum+=model_2->item(i,4)->text().toInt();
    }
    if(ui->vip_id->isEnabled()){
        QString total_money=QString::number(sum);
        total_money.append("元");
        ui->total_pay->setText(total_money);
    }else{
        sum=sum*0.9;
        QString total_money=QString::number(sum);
        total_money.append("元(会员9折)");
        ui->total_pay->setText(total_money);
    }

}

void sellDialog::readMessage()
{
    QString readString = tools->readMessage();
    parser->setMessage(readString);

    QString res=parser->getResult();


    QJsonArray array;
    switch(currentIndex){
    case 0:
        model->clear();
        modelReset();
        array = parser->getItemList();
        for(int i=0;i<array.size();i++){
            QJsonValue ob=array.at(i);
            if(ob.isObject())
            {
                 QJsonObject obj=ob.toObject();
                 QJsonDocument document;
                 document.setObject(obj);
                 QByteArray simpbyte_array = document.toJson(QJsonDocument::Compact);
                 QString str(simpbyte_array);
                 qDebug()<<str;
                 JsonParser *temp=new JsonParser();
                 temp->setMessage(str);
                 model->setItem(i,0,new QStandardItem(temp->getId()));
                 model->item(i,0)->setTextAlignment(Qt::AlignCenter);
                 model->setItem(i,1,new QStandardItem(temp->getName()));
                 model->item(i,1)->setTextAlignment(Qt::AlignCenter);
                 model->setItem(i,2,new QStandardItem(QString::number(temp->getPrice())));
                 model->item(i,2)->setTextAlignment(Qt::AlignCenter);
                 model->setItem(i,3,new QStandardItem(QString::number(temp->getQuantity())));
                 model->item(i,3)->setTextAlignment(Qt::AlignCenter);
                 model->setItem(i,4,new QStandardItem(temp->getSupplier()));
                 model->item(i,4)->setTextAlignment(Qt::AlignCenter);
                 model->setItem(i,5,new QStandardItem(temp->getLastOut()));
                 model->item(i,5)->setTextAlignment(Qt::AlignCenter);
            }
        }
        break;
    case 1:
        if(res.startsWith("true")){
                    ui->vip_id->setDisabled(true);
                    calculateTotalPay();
                }else if(res.startsWith("false")){
                    QMessageBox::information(this,tr("From Server"),"donot have the vip id");
                    ui->vip_id->setText("");
                }
                else if(res.startsWith("success"))
                {
                    QMessageBox::information(this,tr("From Server"),res);
                    model_2->clear();
                    purchaseClear();
                }
                else if(res.startsWith("error"))
                {
                   QMessageBox::information(this,tr("From Server"),res);

                }else{
                    array = parser->getItemList();
                    if(array.size()==0){
                        QMessageBox::information(this,tr("From Server"),"donot have the id");
                    }
                    for(int i=0;i<array.size();i++){
                        QJsonValue ob=array.at(i);
                        if(ob.isObject())
                        {
                             QJsonObject obj=ob.toObject();
                             QJsonDocument document;
                             document.setObject(obj);
                             QByteArray simpbyte_array = document.toJson(QJsonDocument::Compact);
                             QString str(simpbyte_array);
                             qDebug()<<str;
                             JsonParser *temp=new JsonParser();
                             temp->setMessage(str);
                             int num = ui->tableView_2->model()->rowCount();
                             model_2->setItem(num,0,new QStandardItem(temp->getId()));
                             model_2->setItem(num,1,new QStandardItem(temp->getName()));
                             model_2->setItem(num,2,new QStandardItem(ui->in_qty->text()));
                             model_2->setItem(num,3,new QStandardItem(QString::number(temp->getPrice())));
                             double pay=ui->in_qty->text().toInt()*temp->getPrice();
                             model_2->setItem(num,4,new QStandardItem(QString::number(pay)));
                        }
                    }
                    ui->in_code->setText("");
                    ui->in_qty->setText("");
                    calculateTotalPay();
                }
        break;
    }
}

void sellDialog::on_search_clicked()
{
    QString info;
    QString command;
    switch(search_type){
    case 0:
        info=ui->s_id->text().toUpper();
        command=wrapper->wrapSearchItemById(info,"outstock");
        break;
    case 1:
        info=ui->s_id->text();
        command=wrapper->wrapSearchItemBySup(info,"outstock");
        break;
    case 2:
        info=ui->s_id->text();
        command=wrapper->wrapSearchItemByDate(info,"outstock");
        break;
    }
    tools->sendMessage(command);
}




void sellDialog::on_submit_clicked()
{
    QJsonArray array;
    QJsonObject carry;
    int rowSize = ui->tableView_2->model()->rowCount();
    for(int i =0;i<rowSize;i++)
    {

        QJsonObject obj=wrapper->wrapItemToJsonObject(ui->tableView_2->model()->index(i,0).data().toString().toUpper(),
                                          ui->tableView_2->model()->index(i,2).data().toInt());
        array.insert(i,obj);

    }
    carry.insert("items",array);

    tools->sendMessage(wrapper->wrapOutStock(carry));

    if(!ui->vip_id->isEnabled()){
        QString command=wrapper->wrapUpdateVIP(ui->vip_id->text().toUpper(),(int)sum,false);
        tools->sendMessage(command);
    }

}

void sellDialog::on_tabWidget_currentChanged(int index)
{
    currentIndex = index;
}

void sellDialog::on_pushButton_clicked()
{
    QString id = ui->in_code->text().toUpper();


    QString send=wrapper->wrapSearchItemById(id);
    tools->sendMessage(send);


}


void sellDialog::on_delete_item_clicked()
{
    int selected = ui->tableView_2->currentIndex().row();
    ui->tableView_2->model()->removeRow(selected);
    calculateTotalPay();
}

void sellDialog::on_comboBox_currentIndexChanged(int index)
{
    search_type=index;
}

void sellDialog::on_vip_logoff_clicked()
{
    ui->vip_id->setText("");
    ui->vip_id->setEnabled(true);
    calculateTotalPay();
}

void sellDialog::on_vip_login_clicked()
{
    QString command=wrapper->wrapSearchVIP(ui->vip_id->text().toUpper());
    tools->sendMessage(command);

}

void sellDialog::on_toolButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tableView);

    // you can change the column order and
    // choose which colum to export
    obj.addField(0, "商品条码", "char(20)");
    obj.addField(1, "商品名称", "char(20)");
    obj.addField(2, "数量", "char(20)");
    obj.addField(3, "单价", "char(20)");
    obj.addField(4, "供货商", "char(20)");
    obj.addField(5, "日期", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}
