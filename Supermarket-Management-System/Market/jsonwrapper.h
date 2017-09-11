#ifndef JSONWRAPPER_H
#define JSONWRAPPER_H
#include <QString>
#include <QJsonObject>

class JsonWrapper
{
public:
    JsonWrapper();

    QString wrapLogin(QString id,QString pwd);

    QString wrapSignUpPerson(QString id, QString pwd, int admin, QString name,
                             QString sex, QString address,QString phone, QString ID_Number);

    QString wrapUpdatePerson(QString id, QString pwd, int admin, QString name,
                             QString sex, QString address,QString phone, QString ID_Number);

    QString wrapDeletePerson(QString id);

    QString wrapSearchPerson(QString id);

    QString wrapInstock(QString id,QString name,int qty,double price,QString supplier);

    QString wrapOutStock(QJsonObject obj);

    QString wrapSearchItemById(QString id);

    QString wrapSearchItemById(QString id,QString type);

    QString wrapSearchItemBySup(QString name,QString searchType);

    QString wrapSearchItemByDate(QString date,QString searchType);

    QString wrapUpdateItemInfo(QString id,QString name,double price);

    QString wrapUpdateStorageInfo(QString id,QString name,int qty);

    QJsonObject wrapItemToJsonObject(QString id, int quantity);

    QString wrapAddSupplier(QString id,QString name,int type,QString phone);

    QString wrapdeleteSupplier(QString id);

    QString wrapUpdateSupplier(QString id,QString name,int type,QString phone);

    QString wrapSearchSupplier(QString id);

    QString wrapSearchAllSupplier();

    QString wrapSearchSupplierByType(int type);

    QString wrapCreateVIP(QString id,QString name,QString phone);

    QString wrapDeleteVIP(QString id);

    QString wrapUpdateVIP(QString id,int score,bool ret);

    QString wrapSearchVIP(QString id);

    QString wrapExchangeVIP(QString id,int score);

    QString wrapBackUpDB();

    QString wrapClearDB();

    QString wrapLoadDB();
};

#endif // JSONWRAPPER_H
