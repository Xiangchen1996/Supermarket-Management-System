#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QString>
#include <QJsonArray>
class JsonParser
{
public:
    JsonParser();
    QString getResult();
    int getSignal();

    QString getId();
    QString getPassword();
    int getAdmin();
    QString getCreateTime();
    QString getLastLogin();
    QString getName();
    QString getSex();

    int getScore();
    QString getAddress();
    QString getPhone();
    QString getIDNumber();

    QString getSupplier();
    int getQuantity();
    double getPrice();

    QString getLastIn();
    QString getLastOut();

    int getType();

    QJsonArray getItemList();

    QJsonArray getSupplierList();

    void setMessage(QString str);

private:
    QString message;
};

#endif // JSONPARSER_H
