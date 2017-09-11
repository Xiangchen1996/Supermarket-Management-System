#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QString>
#include <QJsonArray>

class JsonParser
{
public:
    JsonParser();

    int getSignal();

    QString getId();
    QString getPassword();
    int getAdmin();
    QString getCreateTime();
    QString getLastLogin();
    QString getname();
    QString getSex();
    QString getAddress();
    QString getPhone();
    QString getIDNumber();

    QString getSearchType();
    int getScore();

    bool getReturn();

    QString getSupplier();
    int getQuantity();
    double getPrice();
    QString getLastIn();

    int getType();

    QJsonArray getOutStockList();


    void reset();
    void setMessage(QString str);

private:
    QString message;
};

#endif // JSONPARSER_H
