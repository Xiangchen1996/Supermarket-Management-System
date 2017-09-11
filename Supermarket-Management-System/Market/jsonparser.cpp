#include "jsonparser.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QDebug>

JsonParser::JsonParser()
{

}

void JsonParser::setMessage(QString str)
{
    message=str;
}

QString JsonParser::getResult()
{
    QJsonParseError error;
    QString result;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("result"))
               {
                   QJsonValue result_value = obj.take("result");
                   if (result_value.isString())
                   {
                       result = result_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"result:"<<result;
    return result;
}

int JsonParser::getSignal()
{
    QJsonParseError error;
    int signal=-1;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               //开始解析json对象
               QJsonObject obj = doucment.object();
               //如果包含name
               if (obj.contains("signal"))
               {
                   QJsonValue signal_value = obj.take("signal");
                   if (signal_value.isDouble())
                   {
                       //转换name
                       signal = signal_value.toVariant().toInt();
                   }
               }
           }
    }
    qDebug()<<"signal:"<<signal;
    return signal;

}

QString JsonParser::getId()
{
    QJsonParseError error;
    QString id;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("id"))
               {
                   QJsonValue id_value = obj.take("id");
                   if (id_value.isString())
                   {
                       id = id_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"id:"<<id;
    return id;
}

QString JsonParser::getPassword()
{
    QJsonParseError error;
    QString pwd;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("password"))
               {
                   QJsonValue pwd_value = obj.take("password");
                   if (pwd_value.isString())
                   {
                       pwd = pwd_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"pwd:"<<pwd;
    return pwd;
}

int JsonParser::getAdmin()
{
    QJsonParseError error;
    int admin;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("admin"))
               {
                   QJsonValue admin_value = obj.take("admin");
                   if (admin_value.isDouble())
                   {
                       admin = admin_value.toVariant().toInt();
                   }
               }
           }
    }
    qDebug()<<"admin:"<<admin;
    return admin;
}

QString JsonParser::getCreateTime()
{
    QJsonParseError error;
    QString createtime;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("createtime"))
               {
                   QJsonValue createtime_value = obj.take("createtime");
                   if (createtime_value.isString())
                   {
                       createtime = createtime_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"createtime:"<<createtime;
    return createtime;
}

QString JsonParser::getLastLogin()
{
    QJsonParseError error;
    QString lastlogin;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("lastlogin"))
               {
                   QJsonValue lastlogin_value = obj.take("lastlogin");
                   if (lastlogin_value.isString())
                   {
                       lastlogin = lastlogin_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"lastlogin:"<<lastlogin;
    return lastlogin;
}

QString JsonParser::getName()
{
    QJsonParseError error;
    QString name;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("name"))
               {
                   QJsonValue name_value = obj.take("name");
                   if (name_value.isString())
                   {
                       name = name_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"name:"<<name;
    return name;
}

QString JsonParser::getSex()
{
    QJsonParseError error;
    QString sex;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("sex"))
               {
                   QJsonValue sex_value = obj.take("sex");
                   if (sex_value.isString())
                   {
                       sex = sex_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"sex:"<<sex;
    return sex;
}

QString JsonParser::getPhone()
{
    QJsonParseError error;
    QString phone;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("phone"))
               {
                   QJsonValue phone_value = obj.take("phone");
                   if (phone_value.isString())
                   {
                       phone = phone_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"phone:"<<phone;
    return phone;
}

QString JsonParser::getIDNumber()
{
    QJsonParseError error;
    QString IDNum;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("ID_Number"))
               {
                   QJsonValue IDNum_value = obj.take("ID_Number");
                   if (IDNum_value.isString())
                   {
                       IDNum = IDNum_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"IDNum:"<<IDNum;
    return IDNum;
}

QString JsonParser::getAddress()
{
    QJsonParseError error;
    QString address;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("address"))
               {
                   QJsonValue address_value = obj.take("address");
                   if (address_value.isString())
                   {
                       address = address_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"address:"<<address;
    return address;
}

QString JsonParser::getSupplier()
{
    QJsonParseError error;
    QString supplier;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("supplier"))
               {
                   QJsonValue supplier_value = obj.take("supplier");
                   if (supplier_value.isString())
                   {
                       supplier = supplier_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"supplier:"<<supplier;
    return supplier;
}

int JsonParser::getQuantity()
{
    QJsonParseError error;
    int quantity;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("quantity"))
               {
                   QJsonValue quantity_value = obj.take("quantity");
                   if (quantity_value.isDouble())
                   {
                       quantity = quantity_value.toVariant().toInt();
                   }
               }
           }
    }
    qDebug()<<"quantity:"<<quantity;
    return quantity;
}

double JsonParser::getPrice()
{
    {
        QJsonParseError error;
        double price;
        QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
        if (error.error == QJsonParseError::NoError)
        {
               if (doucment.isObject())
               {
                   QJsonObject obj = doucment.object();
                   if (obj.contains("price"))
                   {
                       QJsonValue price_value = obj.take("price");
                       if (price_value.isDouble())
                       {
                           price = price_value.toVariant().toDouble();
                       }
                   }
               }
        }
        qDebug()<<"price:"<<price;
        return price;
    }
}

QJsonArray JsonParser::getItemList()
{
    QJsonArray array;
    QJsonParseError error;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("items"))
               {
                   QJsonValue value = obj.take("items");
                   if (value.isArray())
                   {
                       array=value.toArray();
                   }
               }
           }
    }
    qDebug()<<"array:"<<array;
    return array;
}

QJsonArray JsonParser::getSupplierList()
{
    QJsonArray array;
    QJsonParseError error;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("suppliers"))
               {
                   QJsonValue value = obj.take("suppliers");
                   if (value.isArray())
                   {
                       array=value.toArray();
                   }
               }
           }
    }
    qDebug()<<"array:"<<array;
    return array;
}

QString JsonParser::getLastIn()
{
    QJsonParseError error;
    QString last;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("last_in"))
               {
                   QJsonValue last_value = obj.take("last_in");
                   if (last_value.isString())
                   {
                       last = last_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"last:"<<last;
    return last;
}

QString JsonParser::getLastOut()
{
    QJsonParseError error;
    QString last;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("last_out"))
               {
                   QJsonValue last_value = obj.take("last_out");
                   if (last_value.isString())
                   {
                       last = last_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"last:"<<last;
    return last;
}

int JsonParser::getType()
{
    QJsonParseError error;
    int type=-1;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("type"))
               {
                   QJsonValue type_value = obj.take("type");
                   if (type_value.isDouble())
                   {
                       type = type_value.toVariant().toInt();
                   }
               }
           }
    }
    qDebug()<<"type:"<<type;
    return type;
}

int JsonParser::getScore()
{
    QJsonParseError error;
    int score;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("score"))
               {
                   QJsonValue score_value = obj.take("score");
                   if (score_value.isDouble())
                   {
                       score = score_value.toVariant().toInt();
                   }
               }
           }
    }
    qDebug()<<"score:"<<score;
    return score;
}
