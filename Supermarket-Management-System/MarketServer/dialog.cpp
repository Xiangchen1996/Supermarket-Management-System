#include "dialog.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("多线程服务器"));
    statusLabel = new QLabel;

    if (!server.listen(QHostAddress::Any, 1234))
    {
        //
        //QMessageBox::critical 提示对话框
        close();
        return;
    }

    QString ipAddress = QHostAddress(QHostAddress::LocalHost).toString();


    statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n")
                         .arg(ipAddress).arg(server.serverPort()));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    setLayout(mainLayout);


}
