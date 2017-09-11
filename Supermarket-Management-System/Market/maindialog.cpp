#include "maindialog.h"
#include "ui_maindialog.h"
#include <QTimer>
#include <umethod.h>
#include <QThread>
#include <timethread.h>
#include <employeedialog.h>
#include <QMessageBox>
#include <purchasedialog.h>
#include <storagedialog.h>
#include <providerdialog.h>
#include <selldialog.h>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "systemdialog.h"
#include "vipdialog.h"
#include "welcomedialog.h"

extern QString uni_id;
extern QString uni_pwd;
extern TimeThread *time;
extern UMethod *tools;
extern int admin;

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    ui->name->setText(uni_id);
    ui->time->setText(UMethod::getCurrentTime());
//    ui->inStock->setStyleSheet("QPushButton{border-image: url(:/images/images/packing2.png);}");
//                               "QPushButton:hover{border-image: url(:/images/images/packing2_2.png);}"
//                               "QPushButton:pressed{border-image: url(:/images/images/packing2_3.png);}");


    ui->middlelayout->addWidget(new welcomeDialog());
    tools->reset();
    connect(time,SIGNAL(timeReady()),this,SLOT(getTime()));
    connect(tools->client, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

void mainDialog::readMessage()
{
    QMessageBox::information(this, tr("Fortune Client"),
        tools->readMessage());

}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::getTime()
{
    ui->time->setText(UMethod::getCurrentTime());
}





void mainDialog::on_employee_clicked()
{
    if(2==admin){
        //QWidget *child = ui->middlelayout->takeAt(0);

        delete ui->middlelayout->takeAt(0);

        employeeDialog *emp=new employeeDialog();
        ui->middlelayout->addWidget(emp);
        emp->exec();

    }else{
        QMessageBox::information(this, tr("Server"),tr("refuse access"));
    }
}

void mainDialog::on_inStock_clicked()
{
    if(2==admin){

        delete ui->middlelayout->takeAt(0);
        purchaseDialog *pur=new purchaseDialog();
        ui->middlelayout->addWidget(pur);
        pur->exec();
    }else{
        QMessageBox::information(this, tr("Server"),tr("refuse access"));
    }
}

void mainDialog::on_outStock_clicked()
{
    if(2==admin||1==admin){

        delete ui->middlelayout->takeAt(0);
        sellDialog *sell=new sellDialog();
        ui->middlelayout->addWidget(sell);
        sell->exec();

    }else{
        QMessageBox::information(this, tr("Server"),tr("refuse access"));
    }
}

void mainDialog::on_exit_clicked()
{
    this->close();
}

void mainDialog::on_storage_clicked()
{

    if(2==admin||1==admin){

        delete ui->middlelayout->takeAt(0);
        storageDialog *sto=new storageDialog();
        ui->middlelayout->addWidget(sto);
        sto->exec();
    }else{
        QMessageBox::information(this, tr("Server"),tr("refuse access"));
    }
}

void mainDialog::on_supplier_clicked()
{
    if(2==admin){
        delete ui->middlelayout->takeAt(0);
        providerDialog *pro=new providerDialog();
        ui->middlelayout->addWidget(pro);
        pro->exec();
    }else{
        QMessageBox::information(this, tr("Server"),tr("refuse access"));
    }
}

void mainDialog::on_system_clicked()
{
    if(2==admin){
        delete ui->middlelayout->takeAt(0);
        systemDialog *sys=new systemDialog();
        ui->middlelayout->addWidget(sys);
        sys->exec();
    }else{
        QMessageBox::information(this, tr("Server"),tr("refuse access"));
    }
}


void mainDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(mousepressd && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos()- mousePoint);
        e->accept();
    }

}


void mainDialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mousepressd = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void mainDialog::mouseReleaseEvent(QMouseEvent *){
    mousepressd = false;
}

void mainDialog::keyPressEvent(QKeyEvent *e)
{

//    switch(e->key()){
//    case Qt::Key_Enter:
//        ui->login->click();
//        break;
//    case Qt::Key_Return:
//        ui->login->click();
//        break;
//    case Qt::Key_Escape:
//        ui->close->click();
//        break;
//    }
}


void mainDialog::on_min_clicked()
{
    this->showMinimized();
}

void mainDialog::on_vip_clicked()
{
    if(2==admin){
        delete ui->middlelayout->takeAt(0);
        vipDialog *vip=new vipDialog();
        ui->middlelayout->addWidget(vip);
        vip->exec();
    }else{
        QMessageBox::information(this, tr("Server"),tr("refuse access"));
    }
}
