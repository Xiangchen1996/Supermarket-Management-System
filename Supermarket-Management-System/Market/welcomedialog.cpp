#include "welcomedialog.h"
#include "ui_welcomedialog.h"


extern QString uni_id;
welcomeDialog::welcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::welcomeDialog)
{
    ui->setupUi(this);
    ui->name->setText(tr("好再来超市"));
    ui->account->setText(uni_id);
    ui->brief_des->setText(tr("好再来超市：感觉不错就再来"));
}

welcomeDialog::~welcomeDialog()
{
    delete ui;
}
