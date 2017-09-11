#ifndef EMPLOYEEDIALOG_H
#define EMPLOYEEDIALOG_H

#include <QDialog>
#include <jsonparser.h>
#include <jsonwrapper.h>

namespace Ui {
class employeeDialog;
}

class employeeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit employeeDialog(QWidget *parent = 0);
    ~employeeDialog();

private:
    Ui::employeeDialog *ui;
    int currentIndex=0;
    JsonParser *parser;
    JsonWrapper *wrapper;


private slots:
    void getTime();
    void readMessage();
    void searchPerson(QString name);
    void createPerson(QString info);
    void updatePerson(QString info);
    void deletePerson(QString info);
    void on_search_submit_clicked();
    void on_clear_clicked();
    void on_addPerson_clicked();
    void on_request_name_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_submit_delete_clicked();
    void on_update_info_clicked();
    void on_update_clear_clicked();
    void on_submit_update_clicked();

    void widgetEnable();
    void widgetDisable();
};

#endif // EMPLOYEEDIALOG_H
