#ifndef FORTUNETHREAD_H
#define FORTUNETHREAD_H


#include <QThread>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QDateTime>
#include <QMutex>
#include <jsonparser.h>
#include <jsonwrapper.h>


class FortuneThread : QThread
{
    Q_OBJECT
public:
    FortuneThread(int socketDescriptor, QObject *parent , QMutex &mutex);
    void run();
private:
    int socketDescriptor;
    QString theString;
    QTcpSocket *tcpSocket;
    qint16 blockSize;
    QSqlDatabase db;
    QMutex *mutex;
    QString result;

    JsonWrapper *wrapper;
    JsonParser *parser;
    QString command;


    QString MD5encrypt(QString encode);

    void dispatchEvent(const int signal);
    //signal 0:
    void login(const QString uid,const QString pwd);

    //signal 1:
    void signup(const QString c_uid,const QString c_pwd,const int c_admin,const QString c_name,
                const QString c_sex, const QString c_add,const QString c_phone,const QString c_IDnum);

    //signal 2:
    void deletePerson(const QString d_uid);

    //signal 3
    void updatePerson(const QString u_id,const QString u_pwd,const int u_admin,const QString u_name,const QString u_sex,
                      const QString u_add,const QString u_phone,const QString u_IDnum);

    //signal 4:
    void searchPerson(const QString s_uid);


    //signal 5:
    void inStock(const QString g_id,const QString g_name,const int g_qty,const double g_price,const QString g_sup);
    void addNewItem(const QString g_id,const QString g_name,const int g_qty,const double g_price,const QString g_sup);\

    //signal 6:
    void outStockSafe();
    void outStock(QJsonArray array);

    //signal 7:
    void showItemList();

    //signal 8:
    void searchItemById(const QString code);

    //signal 9:
    void updateItemInfo(const QString g_id,const QString g_name,const float g_price);

    //signal 10:
    void updateStorageInfo(const QString g_id,const QString g_name,const int g_qty);


    //signal 11;
    void searchItemBySup(const QString name,QString type);

    //signal 12
    void searchItemByDate(const QString date,QString type);

    //signal 13
    void addSupplier(const QString id,const QString name,const int type,const QString phone);

    //signal 14
    void deleteSupplier(const QString id);

    //signal 15
    void updateSupplier(const QString id,const QString name,const int type,const QString phone);

    //signal 16
    void searchSupplier(const QString id);

    //signal 17
    void searchAllSupplier();

    //signal 18
    void searchSupplierByType(int type);

    //signal 19
    void backUpSql();

    //signal 20
    void clearUpDB();

    //signal 21
    void loadDB();

    //signal 22
    void createVIP(QString id,QString name,QString phone);

    //signal 23
    void deleteVIP(QString id);

    //signal 24
    void updateVIP(QString id,int score,bool ret);

    //signal 25
    void searchVIP(QString id);

    //signal 26
    void exchangeVIP(QString id,int score);

    //signal 27
    void searchItemById(const QString code,QString SearchType);


    void writeToFile(QString info);

    public slots:
        void readMessage();
        void sendMessage();

};

#endif // FORTUNETHREAD_H
