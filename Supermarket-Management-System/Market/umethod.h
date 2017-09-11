#ifndef UMETHOD_H
#define UMETHOD_H
#include <QString>
#include <QTcpSocket>

class UMethod
{
public:
    UMethod();
    void sendMessage(QString string);
    QString readMessage();
    static QString MD5encrypt(QString encode);
    static QString getCurrentTime();
    static QString getCurrentDate();

    QTcpSocket *client;

    void reset();
};

#endif // UMETHOD_H
