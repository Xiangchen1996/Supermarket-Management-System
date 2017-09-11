#ifndef PROVIDERDIALOG_H
#define PROVIDERDIALOG_H

#include <QDialog>
#include <jsonparser.h>
#include <jsonwrapper.h>
#include <QStandardItemModel>

namespace Ui {
class providerDialog;
}

class providerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit providerDialog(QWidget *parent = 0);
    ~providerDialog();

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_add_sup_type_currentIndexChanged(int index);

    void on_update_sup_type_currentIndexChanged(int index);

    void on_request_sup_info_clicked();

    void on_delete_clear_clicked();

    void on_delete_submit_clicked();

    void on_add_clear_clicked();

    void on_add_submit_clicked();

    void on_request_sup_info_2_clicked();

    void on_update_clear_clicked();

    void on_update_submit_clicked();

    void readMessage();
    void getTime();

    void on_search_type_currentIndexChanged(int index);

    void on_search_submit_clicked();

    void on_toolButton_clicked();

private:
    Ui::providerDialog *ui;
    int currentIndex=0;

    int search_type=0;

    JsonParser *parser;
    JsonWrapper *wrapper;

    QStandardItemModel *model;

    int add_type=0;
    int update_type=0;

    void modelReset();

    void updateDisable();
    void updateEnable();


};

#endif // PROVIDERDIALOG_H
