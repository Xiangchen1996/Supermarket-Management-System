#ifndef SYSTEMDIALOG_H
#define SYSTEMDIALOG_H

#include <QDialog>
#include <jsonparser.h>
#include <jsonwrapper.h>

namespace Ui {
class systemDialog;
}

class systemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit systemDialog(QWidget *parent = 0);
    ~systemDialog();

private slots:
    void on_backupDB_clicked();
    void getTime();
    void readMessage();

    void on_clearDB_clicked();

    void on_loadDB_clicked();

private:
    Ui::systemDialog *ui;

    JsonParser *parser;
    JsonWrapper *wrapper;

};

#endif // SYSTEMDIALOG_H
