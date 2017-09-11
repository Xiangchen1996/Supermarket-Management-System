#include "jsonwrapper.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

JsonWrapper::JsonWrapper()
{

}


QString JsonWrapper::wrapLoginResult(QString result,int admin){
    QJsonObject login;
    login.insert("result", result);
    login.insert("admin", admin);
    QJsonDocument document;
    document.setObject(login);
    QByteArray login_array = document.toJson(QJsonDocument::Compact);
    QString str(login_array);
    qDebug() << "wrapLoginResult:" << str;
    return str;
}

QString JsonWrapper::wrapSignUpResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapSignUpResult:" << str;
    return str;
}

QString JsonWrapper::wrapSearchPersonResult(QString id, QString pwd, int admin, QString create_time, QString modify_time,QString last_login, QString name,
                                            QString sex, QString address,QString phone, QString ID_Number)
{
    QJsonObject info;
    info.insert("id", id);
    info.insert("password", pwd);
    info.insert("admin", admin);
    info.insert("create_time", create_time);
    info.insert("modify_time",modify_time);
    info.insert("last_login", last_login);
    info.insert("name", name);
    info.insert("sex", sex);
    info.insert("address",address);
    info.insert("phone", phone);
    info.insert("ID_Number",ID_Number);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapSearchPersonResult:" << str;
    return str;
}

QString JsonWrapper::wrapDeletePersonResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapDeletePersonResult:" << str;
    return str;
}

QString JsonWrapper::wrapUpdatePersonResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapUpdatePersonResult:" << str;
    return str;
}

QString JsonWrapper::wrapDefaultResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapDefaultResult:" << str;
    return str;
}

QString JsonWrapper::wrapInStockResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapInStockResult:" << str;
    return str;
}

QString JsonWrapper::wrapOutStockResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapOutStockResult:" << str;
    return str;
}

QJsonObject JsonWrapper::wrapItemToJsonObject(QString id, QString name, int quantity, double price, QString last_in, QString last_out, QString supplier)
{
    QJsonObject res;
    res.insert("id", id);
    res.insert("name", name);
    res.insert("quantity", quantity);
    res.insert("price", price);
    res.insert("last_in", last_in);
    res.insert("last_out", last_out);
    res.insert("supplier", supplier);
    return res;
}

QString JsonWrapper::wrapShowItemList(QJsonObject res)
{
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapShowItemList:" << str;
    return str;
}

QString JsonWrapper::wrapSearchItemByCodeResult(QJsonObject res)
{
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapSearchItemByCodeResult:" << str;
    return str;
}

QString JsonWrapper::wrapSearchItemBySupplierResult(QJsonObject res)
{
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapSearchItemBySupplierResult:" << str;
    return str;
}

QString JsonWrapper::wrapSearchItemByDateResult(QJsonObject res)
{
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapSearchItemByDateResult:" << str;
    return str;
}

QString JsonWrapper::wrapUpdateItemInfoResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapUpdateItemInfoResult:" << str;
    return str;
}

QString JsonWrapper::wrapUpdateStorageInfoResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapUpdateStorageInfoResult:" << str;
    return str;
}

QString JsonWrapper::wrapAddSupplierResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapAddSupplierResult:" << str;
    return str;
}

QString JsonWrapper::wrapDeleteSupplierResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapDeleteSupplierResult:" << str;
    return str;
}

QString JsonWrapper::wrapUpdateSupplierResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapDeleteSupplierResult:" << str;
    return str;
}

QString JsonWrapper::wrapSearchSupplierResult(QString id, QString name, int type, QString phone)
{
    QJsonObject info;
    info.insert("id", id);
    info.insert("name", name);
    info.insert("type", type);
    info.insert("phone", phone);


    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapSearchSupplierResult:" << str;
    return str;
}

QJsonObject JsonWrapper::wrapSupplierToJsonObject(QString id, QString name, int type, QString phone)
{
    QJsonObject res;
    res.insert("id", id);
    res.insert("name", name);
    res.insert("type", type);
    res.insert("phone", phone);
    return res;
}

QString JsonWrapper::wrapSearchAllSupplierResult(QJsonObject res){
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapSearchAllSupplierResult:" << str;
    return str;
}

QString JsonWrapper::wrapBackUpResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapBackUpResult:" << str;
    return str;
}

QString JsonWrapper::wrapClearDBResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapClearDBResult:" << str;
    return str;
}

QString JsonWrapper::wrapLoadDB(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapLoadDB:" << str;
    return str;
}

QString JsonWrapper::wrapCreateVIPResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapCreateVIPResult:" << str;
    return str;
}

QString JsonWrapper::wrapDeleteVIPResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapDeleteVIPResult:" << str;
    return str;
}

QString JsonWrapper::wrapUpdateVIPResult(QString result)
{
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapUpdateVIPResult:" << str;
    return str;
}

QString JsonWrapper::wrapSearchVIPResult(QString id,QString name,QString phone,int score)
{
    QJsonObject info;
    info.insert("id", id);
    info.insert("name", name);
    info.insert("score", score);
    info.insert("phone", phone);
    info.insert("result","true");
    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapSearchVIPResult:" << str;
    return str;
}

QString JsonWrapper::wrapExchangeVIPResult(QString result){
    QJsonObject res;
    res.insert("result", result);
    QJsonDocument document;
    document.setObject(res);
    QByteArray res_array = document.toJson(QJsonDocument::Compact);
    QString str(res_array);
    qDebug() << "wrapExchangeVIPResult:" << str;
    return str;
}
