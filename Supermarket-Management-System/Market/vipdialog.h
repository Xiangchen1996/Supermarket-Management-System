#ifndef VIPDIALOG_H
#define VIPDIALOG_H

#include <QDialog>
#include <jsonparser.h>
#include <jsonwrapper.h>

namespace Ui {
class vipDialog;
}

class vipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit vipDialog(QWidget *parent = 0);
    ~vipDialog();

private slots:
    void on_search_vip_submit_clicked();
    void getTime();
    void readMessage();

    void on_tabWidget_currentChanged(int index);

    void on_clear_clicked();

    void on_addPerson_clicked();

    void on_request_info_clicked();

    void on_submit_delete_clicked();

    void on_update_clear_clicked();

    void on_submit_update_clicked();

private:
    Ui::vipDialog *ui;
    JsonParser *parser;
    JsonWrapper *wrapper;

    int currentIndex=0;
};

#endif // VIPDIALOG_H
