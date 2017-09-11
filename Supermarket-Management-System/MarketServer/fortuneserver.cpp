#include "fortuneserver.h"
#include "fortunethread.h"

FortuneServer::FortuneServer(QObject *parent)
    : QTcpServer(parent)
{
}

void FortuneServer::incomingConnection(int socketDescriptor)
{
    FortuneThread *thread = new FortuneThread(socketDescriptor, this, mutex);
    thread->run();

}
