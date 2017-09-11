#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>


namespace Ui {
class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

private slots:
    void getTime();

    void readMessage();

    void on_employee_clicked();

    void on_inStock_clicked();

    void on_outStock_clicked();

    void on_exit_clicked();

    void on_storage_clicked();

    void on_supplier_clicked();

    void on_system_clicked();

    void on_min_clicked();

    void on_vip_clicked();

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);


private:
    Ui::mainDialog *ui;

    QPoint mousePoint;//鼠标拖动时的坐标
    bool mousepressd;//用于判断是否按下

};

#endif // MAINDIALOG_H
