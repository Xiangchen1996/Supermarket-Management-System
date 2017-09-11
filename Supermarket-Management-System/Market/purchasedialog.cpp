#include "purchasedialog.h"
#include "ui_purchasedialog.h"
#include <QStandardItemModel>
#include <QLineEdit>
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

purchaseDialog::purchaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::purchaseDialog)
{
    ui->setupUi(this);
    ui->s_id->setPlaceholderText("请输入查询的条件");
//    ui->l_name->setText(uni_id);
//    ui->l_time->setText(tools->getCurrentTime());

    tools->reset();
    connect(tools->client, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(time, SIGNAL(timeReady()), this, SLOT(getTime()));

    parser=new JsonParser();
    wrapper=new JsonWrapper();
    //下面是进货信息查询的tableview
    model = new QStandardItemModel();
    model->setColumnCount(6);
    model->setHeaderData(0,Qt::Horizontal,tr("商品条码"));
    model->setHeaderData(1,Qt::Horizontal,tr("商品名称"));
    model->setHeaderData(2,Qt::Horizontal,tr("单价"));
    model->setHeaderData(3,Qt::Horizontal,tr("数量"));
    model->setHeaderData(4,Qt::Horizontal,tr("供货商"));
    model->setHeaderData(5,Qt::Horizontal,tr("上次进货日期"));

    ui->tableView->setModel(model);
    //表头信息显示居左
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);




}

void purchaseDialog::getTime()
{
  //  ui->l_time->setText(UMethod::getCurrentTime());
}

void purchaseDialog::modelReset()
{
    model->setColumnCount(6);
    model->setHeaderData(0,Qt::Horizontal,tr("商品条码"));
    model->setHeaderData(1,Qt::Horizontal,tr("商品名称"));
    model->setHeaderData(2,Qt::Horizontal,tr("单价"));
    model->setHeaderData(3,Qt::Horizontal,tr("数量"));
    model->setHeaderData(4,Qt::Horizontal,tr("供货商"));
    model->setHeaderData(5,Qt::Horizontal,tr("上次进货日期"));
}

void purchaseDialog::readMessage()
{
    QString readString=tools->readMessage();

    parser->setMessage(readString);
    QString res=parser->getResult();
    if(res.startsWith("success")){
        QMessageBox::information(this, tr("From Server"),res);

    }else{
        model->clear();
        modelReset();
        QJsonArray array = parser->getItemList();
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
                 model->setItem(i,5,new QStandardItem(temp->getLastIn()));
                 model->item(i,5)->setTextAlignment(Qt::AlignCenter);
            }


        }
    }
}

purchaseDialog::~purchaseDialog()
{
    delete ui;
}


void purchaseDialog::on_search_clicked()
{
    QString info;
    QString command;
    switch(search_type){
    case 0:
        info=ui->s_id->text().toUpper();
        command=wrapper->wrapSearchItemById(info,"instock");
        break;
    case 1:
        info=ui->s_id->text();
        command=wrapper->wrapSearchItemBySup(info,"instock");
        break;
    case 2:
        info=ui->s_id->text();
        command=wrapper->wrapSearchItemByDate(info,"instock");
        break;
    }
    tools->sendMessage(command);
}

void purchaseDialog::on_in_clear_clicked()
{
    ui->in_code->setText("");
    ui->in_name->setText("");
    ui->in_price->setText("");
    ui->in_qty->setText("");
    ui->in_sup->setText("");
}

void purchaseDialog::on_in_submit_clicked()
{
    QString command;
    command=wrapper->wrapInstock(ui->in_code->text().toUpper(),ui->in_name->text(),ui->in_qty->text().toInt(),ui->in_price->text().toDouble(),ui->in_sup->text());
    tools->sendMessage(command);
}

void purchaseDialog::on_tabWidget_currentChanged(int index)
{
    currentIndex=index;
}

void purchaseDialog::on_search_type_currentIndexChanged(int index)
{
    search_type=index;
}

void purchaseDialog::on_toolButton_clicked()
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
    obj.addField(2, "单价", "char(20)");
    obj.addField(3, "数量", "char(20)");
    obj.addField(4, "供货商", "char(20)");
    obj.addField(5, "上次进货日期", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}
