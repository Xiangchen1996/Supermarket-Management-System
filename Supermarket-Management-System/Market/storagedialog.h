#ifndef STORAGEDIALOG_H
#define STORAGEDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <jsonparser.h>
#include <jsonwrapper.h>

namespace Ui {
class storageDialog;
}

class storageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit storageDialog(QWidget *parent = 0);
    ~storageDialog();

private:
    Ui::storageDialog *ui;
    QTabWidget *tabWidget;
    int currentIndex=0;

    JsonParser *parser;
    JsonWrapper *wrapper;

    void itemInfo(QString info);
    void storageInfo(QString info);
    void updateInfo(QString info);
    void updateStorage(QString info);

private slots:
    void getTime();
    void readMessage();
    void on_info_submit_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_storage_submit_clicked();
    void on_update_clear_clicked();
    void on_update_request_clicked();
    void on_update_submit_clicked();
    void on_update_storage_request_clicked();
    void on_update_storage_clear_clicked();
    void on_update_storage_submit_clicked();
};

#endif // STORAGEDIALOG_H
