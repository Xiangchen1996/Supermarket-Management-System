#include "umethod.h"
#include <QDataStream>
#include <QCryptographicHash>
#include <QDateTime>
#include <QTcpSocket>



UMethod::UMethod()
{
    client=new QTcpSocket();
    client->abort();
    client->connectToHost("127.0.0.1", 1234);
}

void UMethod::reset()
{
    if(NULL!=client){
        client->abort();
    }
    client=new QTcpSocket();
    client->connectToHost("127.0.0.1", 1234);
}


void UMethod::sendMessage(QString string)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);


    out << (quint16)0;
    out << string;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    client->write(block);
    client->flush();
}

QString UMethod::readMessage()
{
    quint16 blockSize=0;
    QString read;
    QDataStream in(client);
    in.setVersion(QDataStream::Qt_5_5);

    if (blockSize == 0)
    {
        if (client->bytesAvailable() < (int)sizeof(quint16))
            return NULL;
        in >> blockSize;
    }
    if (client->bytesAvailable() < blockSize)
        return NULL;

    in >> read;
    return read;
}

QString UMethod::MD5encrypt(QString encode)
{
    QByteArray byte = encode.toLatin1();
    QByteArray byteMd5 = QCryptographicHash::hash(byte, QCryptographicHash::Md5);
    QString res = byteMd5.toHex();
    return res;
}

QString UMethod::getCurrentTime()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    return str;

}


QString UMethod::getCurrentDate()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd"); //设置显示格式
    return str;
}
