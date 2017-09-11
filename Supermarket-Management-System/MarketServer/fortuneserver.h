#ifndef FORTUNESERVER_H
#define FORTUNESERVER_H


#include <QStringList>
#include <QTcpServer>
#include <QMutex>


class FortuneServer : public QTcpServer
{
    Q_OBJECT
public:
    FortuneServer(QObject *parent = 0);
protected:
    /*当QTcpServer有一个新连接时候调用这个虚函数，socketDescriptor参数是新连接的套接字描述符
    这个函数新建一个QTcpSocket套接字，建立套接字描述符，然后存储套接字在一个整形的待连接链表中。
    最后发射信号newConnection()
    重写这个函数，当一个新连接时候，来调整这个函数的行为。*/
    void incomingConnection(int socketDescriptor);
private:
    QStringList fortunes;
    QMutex mutex;
};

#endif // FORTUNESERVER_H
