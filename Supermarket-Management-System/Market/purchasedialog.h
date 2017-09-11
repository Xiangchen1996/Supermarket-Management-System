#ifndef PURCHASEDIALOG_H
#define PURCHASEDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <jsonparser.h>
#include <jsonwrapper.h>

namespace Ui {
class purchaseDialog;
}

class purchaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit purchaseDialog(QWidget *parent = 0);
    ~purchaseDialog();

private slots:
    void readMessage();
    void getTime();

    void on_search_clicked();

    void on_in_clear_clicked();

    void on_in_submit_clicked();

    void on_tabWidget_currentChanged(int index);


    void on_search_type_currentIndexChanged(int index);

    void on_toolButton_clicked();

private:
    Ui::purchaseDialog *ui;
    int currentIndex=0;
    int search_type=0;
    QStandardItemModel *model;

    JsonParser *parser;
    JsonWrapper *wrapper;

    void modelReset();
};

#endif // PURCHASEDIALOG_H
