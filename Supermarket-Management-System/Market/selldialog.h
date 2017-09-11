#ifndef SELLDIALOG_H
#define SELLDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <jsonparser.h>
#include <jsonwrapper.h>

namespace Ui {
class sellDialog;
}

class sellDialog : public QDialog
{
    Q_OBJECT

public:
    explicit sellDialog(QWidget *parent = 0);
    ~sellDialog();

private slots:
    void readMessage();
    void getTime();

    void on_search_clicked();

    void on_submit_clicked();










    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();

    void on_delete_item_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_vip_logoff_clicked();

    void on_vip_login_clicked();

    void on_toolButton_clicked();

private:
    Ui::sellDialog *ui;
    int currentIndex=0;
    QStandardItemModel *model;
    QStandardItemModel *model_2;

    int search_type=0;

    double sum=0;
    JsonParser *parser;
    JsonWrapper *wrapper;

    void modelReset();
    void purchaseClear();

    void calculateTotalPay();
};

#endif // SELLDIALOG_H
