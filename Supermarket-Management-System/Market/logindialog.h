#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCryptographicHash>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTcpSocket>
#include <QMessageBox>
#include <jsonparser.h>
#include <jsonwrapper.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void login();
    void readMessage();
    void sendMessage();

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);



private slots:

    void on_close_clicked();

    void on_min_clicked();

    void on_login_clicked();


private:
    Ui::Widget *ui;


    QLineEdit *id_edit;
    QLineEdit *pwd_edit;

    JsonParser *parser;
    JsonWrapper *wrapper;

    QPoint mousePoint;//鼠标拖动时的坐标
    bool mousepressd;//用于判断是否按下

};

#endif // WIDGET_H
