#ifndef JSONWRAPPER_H
#define JSONWRAPPER_H
#include <QString>
#include <QJsonObject>

class JsonWrapper
{
public:
    JsonWrapper();

    QString wrapLoginResult(QString result,int admin);

    QString wrapSignUpResult(QString result);

    QString wrapSearchPersonResult(QString id,QString pwd,int admin,QString create_time,QString modify_time,QString last_login,
                                   QString name,QString sex,QString address,QString phone,QString ID_Number);

    QString wrapUpdatePersonResult(QString result);

    QString wrapDeletePersonResult(QString result);

    QString wrapDefaultResult(QString result);

    QString wrapInStockResult(QString result);

    QString wrapOutStockResult(QString result);

    QJsonObject wrapItemToJsonObject(QString id,QString name,int quantity,double price,QString last_in,QString last_out,QString supplier);

    QString wrapShowItemList(QJsonObject res);

    QString wrapSearchItemByCodeResult(QJsonObject res);

    QString wrapSearchItemBySupplierResult(QJsonObject res);

    QString wrapSearchItemByDateResult(QJsonObject res);

    QString wrapUpdateItemInfoResult(QString result);

    QString wrapUpdateStorageInfoResult(QString result);

    QString wrapAddSupplierResult(QString result);

    QString wrapDeleteSupplierResult(QString result);

    QString wrapUpdateSupplierResult(QString result);

    QString wrapSearchSupplierResult(QString id, QString name, int type, QString phone);

    QJsonObject wrapSupplierToJsonObject(QString id,QString name,int type,QString phone);

    QString wrapSearchAllSupplierResult(QJsonObject res);

    QString wrapBackUpResult(QString result);

    QString wrapClearDBResult(QString result);

    QString wrapLoadDB(QString result);

    QString wrapCreateVIPResult(QString result);

    QString wrapDeleteVIPResult(QString result);

    QString wrapUpdateVIPResult(QString result);

    QString wrapSearchVIPResult(QString id,QString name,QString phone,int score);

    QString wrapExchangeVIPResult(QString result);

};

#endif // JSONWRAPPER_H
