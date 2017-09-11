#ifndef TIMETHREAD
#define TIMETHREAD
#include<QThread>
#include<QDebug>
class TimeThread : public QThread
{
    Q_OBJECT

public:
    explicit TimeThread(QObject *parent = 0): QThread(parent)
    {
        //qDebug() << "Time Thread Create : " << QThread::currentThreadId();
    }
    ~TimeThread(){
        //qDebug() << "Time Thread finishd ";
    }


protected:
    virtual void run() Q_DECL_OVERRIDE {
       // qDebug() << "Time Run Thread : " << QThread::currentThreadId();
        while(true){
            msleep(1000);

             // 准备更新
            emit timeReady();
        }
    }



signals:
    void timeReady();
};
#endif // TIMETHREAD

