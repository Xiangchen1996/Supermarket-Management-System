#include "jsonwrapper.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

JsonWrapper::JsonWrapper()
{

}

//0
QString JsonWrapper::wrapLogin(QString id, QString pwd)
{
    QJsonObject login;
    login.insert("signal", 0);
    login.insert("id", id);
    login.insert("password", pwd);
    QJsonDocument document;
    document.setObject(login);
    QByteArray login_array = document.toJson(QJsonDocument::Compact);
    QString str(login_array);
    qDebug() << "wrapLogin:" << str;
    return str;
}
//1
QString JsonWrapper::wrapSignUpPerson(QString id, QString pwd, int admin, QString name,
                                      QString sex, QString address,QString phone, QString ID_Number)
{
    QJsonObject info;
    info.insert("signal",1);
    info.insert("id", id);
    info.insert("password", pwd);
    info.insert("admin", admin);
    info.insert("name", name);
    info.insert("sex", sex);
    info.insert("address",address);
    info.insert("phone", phone);
    info.insert("ID_Number",ID_Number);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapSignUpPerson:" << str;
    return str;
}
//2
QString JsonWrapper::wrapDeletePerson(QString id)
{
    QJsonObject del;
    del.insert("signal", 2);
    del.insert("id", id);
    QJsonDocument document;
    document.setObject(del);
    QByteArray del_array = document.toJson(QJsonDocument::Compact);
    QString str(del_array);
    qDebug() << "wrapDeletePerson:" << str;
    return str;
}
//3
QString JsonWrapper::wrapUpdatePerson(QString id, QString pwd, int admin, QString name,
                                      QString sex, QString address,QString phone, QString ID_Number)
{
    QJsonObject info;
    info.insert("signal",3);
    info.insert("id", id);
    info.insert("password", pwd);
    info.insert("admin", admin);
    info.insert("name", name);
    info.insert("sex", sex);
    info.insert("address",address);
    info.insert("phone", phone);
    info.insert("ID_Number",ID_Number);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapUpdatePerson:" << str;
    return str;
}
//4
QString JsonWrapper::wrapSearchPerson(QString id)
{
    QJsonObject search;
    search.insert("signal", 4);
    search.insert("id", id);
    QJsonDocument document;
    document.setObject(search);
    QByteArray search_array = document.toJson(QJsonDocument::Compact);
    QString str(search_array);
    qDebug() << "wrapSearchPerson:" << str;
    return str;
}
//5
QString JsonWrapper::wrapInstock(QString id, QString name, int qty, double price, QString supplier)
{
    QJsonObject info;
    info.insert("signal",5);
    info.insert("id", id);
    info.insert("name", name);
    info.insert("quantity", qty);
    info.insert("price",price);
    info.insert("supplier", supplier);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapInstock:" << str;
    return str;
}
//6
QString JsonWrapper::wrapOutStock(QJsonObject obj)
{
    obj.insert("signal", 6);
    QJsonDocument document;
    document.setObject(obj);
    QByteArray obj_array = document.toJson(QJsonDocument::Compact);
    QString str(obj_array);
    qDebug() << "wrapOutStock:" << str;
    return str;
}

//8
QString JsonWrapper::wrapSearchItemById(QString id)
{
    QJsonObject search;
    search.insert("signal", 8);
    search.insert("id", id);
    QJsonDocument document;
    document.setObject(search);
    QByteArray search_array = document.toJson(QJsonDocument::Compact);
    QString str(search_array);
    qDebug() << "wrapSearchItemById:" << str;
    return str;
}

QString JsonWrapper::wrapSearchItemById(QString id,QString type)
{
    QJsonObject search;
    search.insert("signal", 27);
    search.insert("id", id);
    search.insert("searchType",type);
    QJsonDocument document;
    document.setObject(search);
    QByteArray search_array = document.toJson(QJsonDocument::Compact);
    QString str(search_array);
    qDebug() << "wrapSearchItemById:" << str;
    return str;
}

QString JsonWrapper::wrapSearchItemBySup(QString name,QString searchType)
{
    QJsonObject search;
    search.insert("signal", 11);
    search.insert("name", name);
    search.insert("searchType",searchType);
    QJsonDocument document;
    document.setObject(search);
    QByteArray search_array = document.toJson(QJsonDocument::Compact);
    QString str(search_array);
    qDebug() << "wrapSearchItemBySup:" << str;
    return str;
}

QString JsonWrapper::wrapSearchItemByDate(QString date,QString searchType)
{
    QJsonObject search;
    search.insert("signal", 12);
    search.insert("last_in", date);
    search.insert("searchType",searchType);
    QJsonDocument document;
    document.setObject(search);
    QByteArray search_array = document.toJson(QJsonDocument::Compact);
    QString str(search_array);
    qDebug() << "wrapSearchItemBySup:" << str;
    return str;
}

QString JsonWrapper::wrapUpdateItemInfo(QString id,QString name,double price)
{
    QJsonObject info;
    info.insert("signal",9);
    info.insert("id", id);
    info.insert("name", name);
    info.insert("price",price);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapUpdateItemInfo:" << str;
    return str;
}

QString JsonWrapper::wrapUpdateStorageInfo(QString id,QString name,int qty)
{
    QJsonObject info;
    info.insert("signal",10);
    info.insert("id", id);
    info.insert("name", name);
    info.insert("quantity", qty);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapUpdateStorageInfo:" << str;
    return str;
}

QJsonObject JsonWrapper::wrapItemToJsonObject(QString id,int quantity)
{
    QJsonObject res;
    res.insert("id", id);
    res.insert("quantity", quantity);
    return res;
}

QString JsonWrapper::wrapAddSupplier(QString id, QString name, int type, QString phone)
{
    QJsonObject info;
    info.insert("signal",13);
    info.insert("id", id);
    info.insert("name", name);
    info.insert("type", type);
    info.insert("phone",phone);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapAddSupplier:" << str;
    return str;
}

QString JsonWrapper::wrapdeleteSupplier(QString id)
{
    QJsonObject info;
    info.insert("signal",14);
    info.insert("id", id);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapDeletePerson:" << str;
    return str;
}

QString JsonWrapper::wrapUpdateSupplier(QString id, QString name, int type, QString phone)
{
    QJsonObject info;
    info.insert("signal",15);
    info.insert("id", id);
    info.insert("name", name);
    info.insert("type", type);
    info.insert("phone",phone);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapUpdateSupplier:" << str;
    return str;
}

QString JsonWrapper::wrapSearchSupplier(QString id)
{
    QJsonObject info;
    info.insert("signal",16);
    info.insert("id", id);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapSearchSupplier:" << str;
    return str;
}

QString JsonWrapper::wrapSearchAllSupplier()
{
    QJsonObject info;
    info.insert("signal",17);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapSearchAllSupplier:" << str;
    return str;
}

QString JsonWrapper::wrapSearchSupplierByType(int type)
{
    QJsonObject info;
    info.insert("signal",18);
    info.insert("type", type);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapSearchSupplierByType:" << str;
    return str;
}

QString JsonWrapper::wrapCreateVIP(QString id, QString name, QString phone)
{
    QJsonObject info;
    info.insert("signal",22);
    info.insert("id", id);
    info.insert("name", name);
    info.insert("phone", phone);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapCreateVIP:" << str;
    return str;
}

QString JsonWrapper::wrapDeleteVIP(QString id)
{
    QJsonObject info;
    info.insert("signal",23);
    info.insert("id", id);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapDeleteVIP:" << str;
    return str;
}

QString JsonWrapper::wrapUpdateVIP(QString id, int score,bool ret)
{
    QJsonObject info;
    info.insert("signal",24);
    info.insert("id", id);
    info.insert("score", score);
    info.insert("return",ret);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapUpdateVIP:" << str;
    return str;
}

QString JsonWrapper::wrapSearchVIP(QString id)
{
    QJsonObject info;
    info.insert("signal",25);
    info.insert("id", id);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapSearchVIP:" << str;
    return str;
}

QString JsonWrapper::wrapExchangeVIP(QString id, int score)
{
    QJsonObject info;
    info.insert("signal",26);
    info.insert("id", id);
    info.insert("score", score);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapExchangeVIP:" << str;
    return str;
}

QString JsonWrapper::wrapBackUpDB()
{
    QJsonObject info;
    info.insert("signal",19);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapBackUpDB:" << str;
    return str;
}

QString JsonWrapper::wrapClearDB()
{
    QJsonObject info;
    info.insert("signal",20);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapClearDB:" << str;
    return str;
}

QString JsonWrapper::wrapLoadDB()
{
    QJsonObject info;
    info.insert("signal",21);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapLoadDB:" << str;
    return str;
}
