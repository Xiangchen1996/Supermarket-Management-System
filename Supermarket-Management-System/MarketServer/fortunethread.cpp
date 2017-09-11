#include "fortunethread.h"
#include <QDataStream>
#include <QSqlError>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <jsonparser.h>
#include <QCryptographicHash>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QProcess>
#include <QStringList>



FortuneThread::FortuneThread(int socketDescriptor, QObject *parent, QMutex &mutex)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
    blockSize = 0;
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mysql");
    db.setUserName("root");
    db.setPassword("");
    db.setPort(3306);
    parser=new JsonParser();
    wrapper=new JsonWrapper();
    this->mutex=&mutex;

}

void FortuneThread::backUpSql()
{
    QString Cmd="C:\\Program Files\\MySQL\\MySQL Server 5.7\\bin\\mysqldump.exe";
    QStringList argument;
    argument<<"-uroot"<<"-proot"<<"--add-drop-table"<<"mysql";
    QString Path=QString("%1").arg("./backup.Sql");
    QProcess *poc=new QProcess;
    poc->setStandardOutputFile(Path);
    poc->start(Cmd,argument);
    poc->waitForFinished(-1);
    result=wrapper->wrapBackUpResult("success to backUp");
    QString info="//backUp DataBase";
    writeToFile(info);
    sendMessage();
}

void FortuneThread::loadDB()
{
    QString Cmd="C:\\Program Files\\MySQL\\MySQL Server 5.7\\bin\\mysql.exe";
    QStringList argument;
    argument<<"-uroot"<<"-proot"<<"mysql";
    QString Path=QString("%1").arg("./backup.Sql");
    QProcess *poc=new QProcess;
    poc->setStandardInputFile(Path);
    poc->start(Cmd,argument);
    poc->waitForFinished(-1);
    result=wrapper->wrapLoadDB("success to loadDB");
    QString info="//clearUp DataBase";
    writeToFile(info);
    sendMessage();
}

void FortuneThread::clearUpDB()
{
    QSqlQuery query(db);
    query.exec("TRUNCATE TABLE employee");
    qDebug()<<query.lastError();
    query.exec("TRUNCATE TABLE goods");
    qDebug()<<query.lastError();
    query.exec("TRUNCATE TABLE instock");
    qDebug()<<query.lastError();
    query.exec("TRUNCATE TABLE outstock");
    qDebug()<<query.lastError();
    query.exec("TRUNCATE TABLE supplier");
    qDebug()<<query.lastError();
    query.exec("TRUNCATE TABLE vip");
    qDebug()<<query.lastError();

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    query.exec("insert into employee values(?,?,?,?,?,?,?,?,?,?)");
    query.bindValue(0,"root");
    query.bindValue(1,"root");
    query.bindValue(2,2);
    query.bindValue(3,time);
    query.bindValue(4,NULL);
    query.bindValue(5,NULL);
    query.bindValue(6,"Lee");
    query.bindValue(7,"male");
    query.bindValue(8,"NEU");
    query.bindValue(9,"13131313131");
    query.bindValue(10,"4141414114141414");
    qDebug()<<query.lastError();

    QString info="//load DataBase";
    writeToFile(info);
    result=wrapper->wrapClearDBResult("success to clearDB");
    sendMessage();

}

void FortuneThread::run()
{
    tcpSocket = new QTcpSocket;
    //将Server传来的socketDescriptor与刚创建的tcpSocket关联
    qDebug()<<"run";
    if (!tcpSocket->setSocketDescriptor(socketDescriptor))
    {
        return;
    }
    //Qt::AutoConnection表示系统自动选择相应的连接方式，
    //如果信号与槽在同一线程，就采用Qt::DirectConnection,一旦信号产生，立即执行槽函数。
    connect(tcpSocket, SIGNAL(readyRead()), this,
        SLOT(readMessage()), Qt::DirectConnection);
    exec();

}

void FortuneThread::readMessage()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_5);
    if (blockSize == 0)
    {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }
    if (tcpSocket->bytesAvailable() < blockSize)
        return;

    in >> theString;

    blockSize = 0;
    qDebug() << theString;
    //important
    parser->setMessage(theString);
    //
    int signal=parser->getSignal();



    dispatchEvent(signal);
}

void FortuneThread::writeToFile(QString info)
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    QString fileName="./log.txt";
    QFile file(fileName);
    if(!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug()<<"cannot open file";

    }else{
        QTextStream in(&file);
        in<<info<<"   "<<str<<"\n";
        file.close();
    }
}

//分发服务器对应方法
void FortuneThread::dispatchEvent(const int signal)
{

    mutex->lock();
    if(!db.open()){
        result=wrapper->wrapDefaultResult("error:cannot open db");
        sendMessage();
    }else{
        switch (signal) {
//protocol -----------------------------------------------------------------------------------------------
//#every time op check the id#
//Login
//CreatePerson
//DeletePerson
//searchPerson
//updatePerson
//InStock
//OutStock
//AddNewItem
//
//searchItem
//updateItemInfo
//updateStorageInfo
//
//
//
//
//protocol -----------------------------------------------------------------------------------------------

        case 0:
            login(parser->getId(),parser->getPassword());
            break;
        case 1:
            signup(parser->getId(),parser->getPassword(),parser->getAdmin(),
                    parser->getname(),parser->getSex(),parser->getAddress()
                    ,parser->getPhone(),parser->getIDNumber());
            break;
        case 2:
            deletePerson(parser->getId());
            break;

        case 3:
            updatePerson(parser->getId(),parser->getPassword(),parser->getAdmin(),
                         parser->getname(),parser->getSex(),parser->getAddress()
                         ,parser->getPhone(),parser->getIDNumber());
            break;
        case 4:
            searchPerson(parser->getId());
            break;

        case 5:
            inStock(parser->getId(),parser->getname(),parser->getQuantity(),parser->getPrice(),parser->getSupplier());
            break;
        case 6:
            outStockSafe();
            break;
        case 7:
            showItemList();
            break;
        case 8:
            searchItemById(parser->getId());
            break;
        case 9:
            updateItemInfo(parser->getId(),parser->getname(),parser->getPrice());
            break;
        case 10:
            updateStorageInfo(parser->getId(),parser->getname(),parser->getQuantity());
            break;
        case 11:
            searchItemBySup(parser->getname(),parser->getSearchType());
            break;
        case 12:
            searchItemByDate(parser->getLastIn(),parser->getSearchType());
            break;
        case 13:
            addSupplier(parser->getId(),parser->getname(),parser->getType(),parser->getPhone());
            break;
        case 14:
            deleteSupplier(parser->getId());
            break;
        case 15:
            updateSupplier(parser->getId(),parser->getname(),parser->getType(),parser->getPhone());
            break;
        case 16:
            searchSupplier(parser->getId());
            break;
        case 17:
            searchAllSupplier();
            break;
        case 18:
            searchSupplierByType(parser->getType());
            break;
        case 19:
            backUpSql();
            break;
        case 20:
            clearUpDB();
            break;
        case 21:
            loadDB();
            break;
        case 22:
            createVIP(parser->getId(),parser->getname(),parser->getPhone());
            break;
        case 23:
            deleteVIP(parser->getId());
            break;
        case 24:
            updateVIP(parser->getId(),parser->getScore(),parser->getReturn());
            break;
        case 25:
            searchVIP(parser->getId());
            break;
        case 26:
            exchangeVIP(parser->getId(),parser->getScore());
            break;
        case 27:
            searchItemById(parser->getId(),parser->getSearchType());
            break;
        default:
            sendMessage();
            break;
        }
        db.close();

    }
    mutex->unlock();


}

QString FortuneThread::MD5encrypt(QString encode)
{
    QByteArray byte = encode.toLatin1();
    QByteArray byteMd5 = QCryptographicHash::hash(byte, QCryptographicHash::Md5);
    QString res = byteMd5.toHex();
    return res;
}

void FortuneThread::login(const QString uid,const QString pwd)
{

    QSqlQuery query(db);
    query.exec("select * from employee");
    //default

    result="error : id or password is wrong";

    QString md5_id="";
    QString md5_pwd="";

    while(query.next()){
        QString value0=query.value(0).toString();//uid
        QString value1=query.value(1).toString();//psw
        int value2=query.value(2).toInt();//admin


        md5_id = MD5encrypt(value0);
        md5_pwd = MD5encrypt(value1);


        if(0==md5_id.compare(uid)&&0==md5_pwd.compare(pwd)){
            QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
            //QString str = time.toString("yyyy-MM-dd"); //设置显示格式

            query.prepare(tr("update employee set last_login = ? where id = ?"));
            query.bindValue(0,time);
            query.bindValue(1,value0);
            query.exec();
            qDebug()<<query.lastError();
            result=wrapper->wrapLoginResult("success",value2);
            QString info=value0;
            info.append("   login");
            writeToFile(info);
            break;
        }
    }
    sendMessage();
}

void FortuneThread::signup(const QString c_uid,const QString c_pwd,const int c_admin,const QString c_name,
                           const QString c_sex, const QString c_add,const QString c_phone,const QString c_IDnum)
{
    QSqlQuery query(db);
    query.exec("select * from employee");
    //default

    result=wrapper->wrapSignUpResult("error:already has the id");
    bool hasNoRecord=true;

    while(query.next()){
        QString value0=query.value(0).toString();//uid
        if(hasNoRecord&&0==value0.compare(c_uid)){
            hasNoRecord=false;
            break;
        }

    }
    if(hasNoRecord){
        QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
        query.prepare(tr("insert into employee values(?,?,?,?,?,?,?,?,?,?)"));
        query.bindValue(0,c_uid);
        query.bindValue(1,c_pwd);
        query.bindValue(2,c_admin);
        query.bindValue(3,time);
        query.bindValue(4,NULL);
        query.bindValue(5,c_name);
        query.bindValue(6,c_sex);
        query.bindValue(7,c_add);
        query.bindValue(8,c_phone);
        query.bindValue(9,c_IDnum);
        query.exec();
        qDebug() << query.lastError();
        result=wrapper->wrapSignUpResult("success to create");

        QString info="create User ";
        info.append(c_uid);
        writeToFile(info);

    }
    sendMessage();
}


void FortuneThread::searchPerson(const QString s_uid)
{

    QSqlQuery query(db);
    query.prepare("select * from employee where id = ?");
    query.bindValue(0,s_uid);
    query.exec();
    //default

    result=wrapper->wrapDefaultResult("error:Nothing to show");
    while(query.next()){
        QString value0=query.value(0).toString();//uid
        QString value1=query.value(1).toString();//psw
        int value2=query.value(2).toInt();//admin
        QString value3=query.value(3).toString();//create time
        QString value4=query.value(4).toString();//modify_time
        QString value5=query.value(5).toString();//last login
        QString value6=query.value(6).toString();//name
        QString value7=query.value(7).toString();//sex
        QString value8=query.value(8).toString();//address
        QString value9=query.value(9).toString();//phone
        QString value10=query.value(10).toString();//ID number

        if(0==s_uid.compare(value0)){
            result=wrapper->wrapSearchPersonResult(value0,value1,value2,value3,value4,value5,value6,value7,value8,value9,value10);
        }
    }
    sendMessage();

}



void FortuneThread::deletePerson(const QString d_uid)
{
    QSqlQuery query(db);
    query.exec("select * from employee");
    //default

    result=wrapper->wrapDeletePersonResult("error:donnot have the id");

    bool hasPerson=false;
    while(query.next()){
        QString value0=query.value(0).toString();//uid
        if(!hasPerson&&0==value0.compare(d_uid)){
            hasPerson=true;
            break;
        }
    }

    if(hasPerson){
        query.clear();
        query.prepare(tr("delete from employee where id = ? "));
        query.bindValue(0,d_uid);
        query.exec();
        qDebug()<<query.lastError();
        result=wrapper->wrapDeletePersonResult("success to delete");

        QString info="delete User ";
        info.append(d_uid);
        writeToFile(info);
    }
    sendMessage();
}

void FortuneThread::updatePerson(const QString u_id,const QString u_pwd,const int u_admin,const QString u_name,const QString u_sex,
                                 const QString u_add,const QString u_phone,const QString u_IDnum)
{

    QSqlQuery query(db);
    query.exec("select * from employee");
    //default

    result=wrapper->wrapUpdatePersonResult("error : dont have this person");

    bool hasRecord=false;

    while(query.next()){
        QString value0=query.value(0).toString();//uid    
        if(!hasRecord&&0==value0.compare(u_id)){
            hasRecord=true;
            break;
        }
    }

    if(hasRecord){
        query.clear();
        QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
        query.prepare(tr("update employee set password = ? , admin = ? ,"
                         "name = ? , sex = ? , address = ? , phone_number = ? ,"
                         "ID_number = ? ,modify_time = ? where id = ? "));
        query.bindValue(0,u_pwd);
        query.bindValue(1,u_admin);
        query.bindValue(2,u_name);
        query.bindValue(3,u_sex);
        query.bindValue(4,u_add);
        query.bindValue(5,u_phone);
        query.bindValue(6,u_IDnum);
        query.bindValue(7,time);
        query.bindValue(8,u_id);
        query.exec();
        qDebug() << query.lastError();
        result=wrapper->wrapUpdatePersonResult("success to update");

        QString info="update User ";
        info.append(u_id);
        writeToFile(info);

    }
    sendMessage();

}

void FortuneThread::inStock(const QString g_id,const QString g_name,const int g_qty,const double g_price,const QString g_sup)
{
    QSqlQuery query(db);
    query.exec("select * from goods");
    //default

    bool hasGoods=false;
    int qty=0;

    while(query.next()){
        QString value0=query.value(0).toString();//uid
        if(0==g_id.compare(value0)){
            qty=query.value(2).toInt();
            hasGoods=true;
            break;
        }
    }

    if(hasGoods){
        query.clear();
        QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
        //QString str = time.toString("yyyy-MM-dd"); //设置显示格式
        query.prepare(tr("update goods set quantity = ? ,last_in = ? ,supplier = ? where id = ?"));
        query.bindValue(0,qty+g_qty);
        query.bindValue(1,time);
        query.bindValue(2,g_sup);
        query.bindValue(3,g_id);
        query.exec();
        qDebug()<<query.lastError();
        result=wrapper->wrapInStockResult("success to instock");

        QString info="instock   ";
        info.append(g_id);
        info.append("   ");
        info.append(g_name);
        info.append("   ");
        info.append(qty);

        writeToFile(info);


        query.clear();
        query.exec("select max(id) from instock");
        query.next();
        int value=query.value(0).toInt()+1;
        query.clear();

        query.prepare(tr("insert into instock values(?,?,?,?,?,?)"));
        query.bindValue(0,value);
        query.bindValue(1,g_id);
        query.bindValue(2,g_qty);
        query.bindValue(3,g_price);
        query.bindValue(4,time);
        query.bindValue(5,g_sup);
        query.exec();
        qDebug()<<query.lastError();

        sendMessage();

    }else{
        addNewItem(g_id,g_name,g_qty,g_price,g_sup);
    }

}

void FortuneThread::outStockSafe()
{
    QJsonArray array=parser->getOutStockList();
    bool isAllSafe=true;
    for (int i = 0; i < array.size(); i++){
          QJsonValue arrayValue = array.at(i);
          if (arrayValue.isObject())
          {
               QJsonObject obj=arrayValue.toObject();
               QJsonDocument document;
               document.setObject(obj);
               QByteArray simpbyte_array = document.toJson(QJsonDocument::Compact);
               QString str(simpbyte_array);
               JsonParser *temp=new JsonParser();
               temp->setMessage(str);

               QString code=temp->getId();
               int qty=temp->getQuantity();

               QSqlQuery query(db);
               query.exec("select * from goods");
               int has=0;
               while(query.next()){
                   QString value0=query.value(0).toString();//uid
                   if(0==code.compare(value0)){
                       has=query.value(2).toInt();
                       break;
                   }
               }
               if(qty>has){
                   isAllSafe=false;
                   result=wrapper->wrapOutStockResult(tr("error:out of stock(code:%1)").arg(code));
                   break;
               }

          }
    }
    if(isAllSafe){
        outStock(array);
    }else{
        sendMessage();
    }

}

void FortuneThread::outStock(QJsonArray array)
{

    for (int i = 0; i < array.size(); i++){
          QJsonValue arrayValue = array.at(i);
          if (arrayValue.isObject())
          {
              QJsonObject obj=arrayValue.toObject();
              QJsonDocument document;
              document.setObject(obj);
              QByteArray simpbyte_array = document.toJson(QJsonDocument::Compact);
              QString str(simpbyte_array);
              JsonParser *temp=new JsonParser();
              temp->setMessage(str);

              QString code=temp->getId();
              int qty=temp->getQuantity();
              double price;
              QString sup;
              QString name;

              QSqlQuery query(db);
              query.exec("select * from goods");
              int has=0;
              while(query.next()){
                  QString value0=query.value(0).toString();//uid
                  if(0==code.compare(value0)){
                      name=query.value(1).toString();
                      has=query.value(2).toInt();
                      price=query.value(3).toDouble();
                      sup=query.value(6).toString();
                      break;
                  }
              }

              query.clear();
              QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
              //QString str = time.toString("yyyy-MM-dd"); //设置显示格式
              query.prepare(tr("update goods set quantity = ? ,last_out = ?  where id = ?"));

              query.bindValue(0,has-qty);
              query.bindValue(1,time);
              query.bindValue(2,code);
              query.exec();
              qDebug()<<query.lastError();
              result=wrapper->wrapOutStockResult("success to outstock");

              QString info="outstock   ";
              info.append(code);
              info.append("   ");
              info.append(name);
              info.append("   ");
              info.append(qty);
              writeToFile(info);

              query.clear();
              query.exec("select max(id) from outstock");
              query.next();
              int value=query.value(0).toInt()+1;
              query.clear();

              query.prepare(tr("insert into outstock values(?,?,?,?,?,?,?)"));
              query.bindValue(0,value);
              query.bindValue(1,code);
              query.bindValue(2,name);
              query.bindValue(2,qty);
              query.bindValue(3,price);
              query.bindValue(4,time);
              query.bindValue(5,sup);
              query.exec();
              qDebug()<<query.lastError();

          }
    }
    sendMessage();
}

void FortuneThread::addNewItem(const QString g_id,const QString g_name,const int g_qty,const double g_price,const QString g_sup)
{
    QSqlQuery query(db);
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    //QString str = time.toString("yyyy-MM-dd"); //设置显示格式
    query.prepare(tr("insert into goods values(?,?,?,?,?,?,?)"));
    query.bindValue(0,g_id);
    query.bindValue(1,g_name);
    query.bindValue(2,g_qty);
    query.bindValue(3,g_price);
    query.bindValue(4,time);
    query.bindValue(5,NULL);
    query.bindValue(6,g_sup);
    query.exec();
    qDebug()<<query.lastError();
    result=wrapper->wrapInStockResult("success to addNewItem");

    QString info="addNewItem   ";
    info.append(g_id);
    info.append("   ");
    info.append(g_name);
    info.append("   ");
    info.append(g_qty);
    writeToFile(info);

    query.clear();
    query.exec("select max(id) from instock");
    query.next();
    int value=query.value(0).toInt()+1;
    query.clear();

    query.prepare(tr("insert into instock values(?,?,?,?,?,?,?)"));
    query.bindValue(0,value);
    query.bindValue(1,g_id);
    query.bindValue(2,g_name);
    query.bindValue(3,g_qty);
    query.bindValue(4,g_price);
    query.bindValue(5,time);
    query.bindValue(6,g_sup);
    query.exec();
    qDebug()<<query.lastError();

    sendMessage();

}


void FortuneThread::showItemList()
{
    QSqlQuery query(db);
    query.exec("select * from goods");
    //default


    QJsonArray array;
    QJsonObject carry;
    carry.insert("items",array);

    int count=0;
    while(query.next()){
        QString value0=query.value(0).toString();//id
        QString value1=query.value(1).toString();//name
        int value2=query.value(2).toInt();//quantity
        double value3=query.value(3).toDouble();//price
        QString value4=query.value(4).toString();//last_in
        QString value5=query.value(5).toString();//last_out
        QString value6=query.value(6).toString();//supplier

        QJsonObject obj=wrapper->wrapItemToJsonObject(value0,value1,value2,value3,value4,value5,value6);
        array.insert(count++,obj);

        result=wrapper->wrapShowItemList(carry);

    }
    sendMessage();
}

void FortuneThread::searchItemById(const QString code)
{
    QSqlQuery query(db);
    query.prepare("select * from goods where id = ?");
    query.bindValue(0,code);
    query.exec();
    //default

    QJsonArray array;
    QJsonObject carry;

    int count=0;
    while(query.next()){
        QString value0=query.value(0).toString();//id
        QString value1=query.value(1).toString();//name
        int value2=query.value(2).toInt();//quantity
        double value3=query.value(3).toDouble();//price
        QString value4=query.value(4).toString();//last_in
        QString value5=query.value(5).toString();//last_out
        QString value6=query.value(6).toString();//supplier
        QJsonObject obj=wrapper->wrapItemToJsonObject(value0,value1,value2,value3,value4,value5,value6);
        array.insert(count++,obj);


    }
    carry.insert("items",array);
    result=wrapper->wrapSearchItemByCodeResult(carry);
    sendMessage();
}

void FortuneThread::searchItemById(const QString code, QString SearchType)
{
    QSqlQuery query(db);
    QString command="select * from ";
    command.append(SearchType);
    command.append(" where good_id = ?");
    query.prepare(command);
    query.bindValue(0,code);
    query.exec();
    //default

    qDebug()<<command;

    QJsonArray array;
    QJsonObject carry;

    int count=0;
    while(query.next()){
        QString value0=query.value(1).toString();//id
        QString value1=query.value(2).toString();//name
        int value2=query.value(3).toInt();//quantity
        double value3=query.value(4).toDouble();//price
        QString value4=query.value(5).toString();//date
        QString value5=query.value(6).toString();//supplier
        QJsonObject obj;
        qDebug()<<value0;
        if(SearchType.startsWith("instock")){
            obj=wrapper->wrapItemToJsonObject(value0,value1,value2,value3,value4,NULL,value5);
        }else{
            obj=wrapper->wrapItemToJsonObject(value0,value1,value2,value3,NULL,value4,value5);
        }

        array.insert(count++,obj);


    }
    carry.insert("items",array);
    result=wrapper->wrapSearchItemByCodeResult(carry);
    sendMessage();
}

void FortuneThread::updateItemInfo(const QString g_id,const QString g_name,const float g_price)
{
    QSqlQuery query(db);
    query.prepare("select * from goods where id = ?");
    query.bindValue(0,g_id);
    query.exec();
    //default

    bool hasGoods=false;
    while(query.next()){
        QString value0=query.value(0).toString();//uid
        if(0==g_id.compare(value0)){
            hasGoods=true;
            break;
        }
    }

    if(hasGoods){
        query.clear();
        query.prepare(tr("update goods set name = ?,price = ? where id = ?"));
        query.bindValue(0,g_name);
        query.bindValue(1,g_price);
        query.bindValue(2,g_id);
        query.exec();
        qDebug()<<query.lastError();
        result=wrapper->wrapUpdateItemInfoResult("success to updateItem");
        QString info="update   Goods   ";
        info.append(g_id);
        info.append("   ");
        info.append(g_name);
        writeToFile(info);
    }else{
        result=wrapper->wrapUpdateItemInfoResult("error : no such item");
    }
    sendMessage();
}

void FortuneThread::updateStorageInfo(const QString g_id,const QString g_name,const int g_qty)
{
    QSqlQuery query(db);
    query.prepare("select * from goods where id = ?");
    query.bindValue(0,g_id);
    query.exec();
    //default

    bool hasGoods=false;

    while(query.next()){
        QString value0=query.value(0).toString();//uid
        if(0==g_id.compare(value0)){
            hasGoods=true;
            break;
        }
    }

    if(hasGoods){
        query.clear();
        query.prepare(tr("update goods set name = ?,quantity = ? where id = ?"));
        query.bindValue(0,g_name);
        query.bindValue(1,g_qty);
        query.bindValue(2,g_id);
        query.exec();
        qDebug()<<query.lastError();
        result=wrapper->wrapUpdateStorageInfoResult("success to updateStorage");

        QString info="update   Goods   ";
        info.append(g_id);
        info.append("   ");
        info.append(g_name);
        writeToFile(info);
    }else{
        result=wrapper->wrapUpdateStorageInfoResult("error : no such item");
    }
    sendMessage();
}

void FortuneThread::searchItemBySup(const QString name,QString type)
{
    QSqlQuery query(db);
    QString command="select * from ";
    command.append(type);
    command.append(" where supplier = ?");
    query.prepare(command);
    query.bindValue(0,name);
    query.exec();
    //default

    QJsonArray array;
    QJsonObject carry;

    int count=0;
    while(query.next()){
        QString value0=query.value(1).toString();//id
        QString value1=query.value(2).toString();//name
        int value2=query.value(3).toInt();//quantity
        double value3=query.value(4).toDouble();//price
        QString value4=query.value(5).toString();//date
        QString value5=query.value(6).toString();//supplier
        QJsonObject obj;
        if(type.startsWith("instock")){
            obj=wrapper->wrapItemToJsonObject(value0,value1,value2,value3,value4,NULL,value5);
        }else{
            obj=wrapper->wrapItemToJsonObject(value0,value1,value2,value3,NULL,value5,value5);
        }
        array.insert(count++,obj);


    }
    carry.insert("items",array);
    result=wrapper->wrapSearchItemBySupplierResult(carry);
    sendMessage();
}

void FortuneThread::searchItemByDate(const QString date,QString type)
{
    QSqlQuery query(db);
    QString command="select * from ";
    command.append(type);
    command.append(" where date = ?");
    query.prepare(command);
    query.bindValue(0,date);
    query.exec();
    //default

    QJsonArray array;
    QJsonObject carry;

    int count=0;
    while(query.next()){
        QString value0=query.value(1).toString();//id
        QString value1=query.value(2).toString();//name
        int value2=query.value(3).toInt();//quantity
        double value3=query.value(4).toDouble();//price
        QString value4=query.value(5).toString();//date
        QString value5=query.value(6).toString();//supplier
        QJsonObject obj;
        if(type.startsWith("instock")){
            obj=wrapper->wrapItemToJsonObject(value0,value1,value2,value3,value4,NULL,value5);
        }else{
            obj=wrapper->wrapItemToJsonObject(value0,value1,value2,value3,NULL,value5,value5);
        }
        array.insert(count++,obj);


    }
    carry.insert("items",array);
    result=wrapper->wrapSearchItemBySupplierResult(carry);
    sendMessage();
}

void FortuneThread::addSupplier(const QString id, const QString name, const int type, const QString phone)
{
    QSqlQuery query(db);
    query.exec("select * from supplier");
    //default


    bool hasNoRecord=true;

    while(query.next()){
        QString value0=query.value(0).toString();//uid
        if(hasNoRecord&&0==value0.compare(id)){
            hasNoRecord=false;
            result=wrapper->wrapAddSupplierResult("error:already has the id");
            break;
        }

    }
    if(hasNoRecord){
        query.prepare(tr("insert into supplier values(?,?,?,?)"));
        query.bindValue(0,id);
        query.bindValue(1,name);
        query.bindValue(2,phone);
        query.bindValue(3,type);


        query.exec();
        qDebug() << query.lastError();
        result=wrapper->wrapAddSupplierResult("success to add");

        QString info="add   Supplier   ";
        info.append(id);
        info.append("   ");
        info.append(name);
        writeToFile(info);

    }
    sendMessage();
}

void FortuneThread::deleteSupplier(const QString id)
{
    QSqlQuery query(db);
    query.exec("select * from supplier");
    //default

    result=wrapper->wrapDeleteSupplierResult("error:donnot have the id");

    bool hasPerson=false;
    QString name;
    while(query.next()){
        QString value0=query.value(0).toString();//uid
        if(!hasPerson&&0==value0.compare(id)){
            hasPerson=true;
            name=value0;
            break;
        }
    }

    if(hasPerson){
        query.clear();
        query.prepare(tr("delete from supplier where id = ? "));
        query.bindValue(0,id);
        query.exec();
        qDebug()<<query.lastError();
        result=wrapper->wrapDeleteSupplierResult("success to delete");

        QString info="delete   Supplier   ";
        info.append(id);
        info.append("   ");
        info.append(name);
        writeToFile(info);
    }
    sendMessage();
}

void FortuneThread::updateSupplier(const QString id, const QString name, const int type, const QString phone)
{
    QSqlQuery query(db);
    query.exec("select * from supplier");
    //default

    result=wrapper->wrapUpdateSupplierResult("error : dont have this supplier");

    bool hasRecord=false;

    while(query.next()){
        QString value0=query.value(0).toString();//uid
        if(!hasRecord&&0==value0.compare(id)){
            hasRecord=true;
            break;
        }
    }

    if(hasRecord){
        query.clear();
        query.prepare(tr("update supplier set name = ? , phone = ? ,"
                         "type = ?  where id = ? "));
        query.bindValue(0,name);
        query.bindValue(1,phone);
        query.bindValue(2,type);
        query.bindValue(3,id);
        query.exec();
        qDebug() << query.lastError();
        result=wrapper->wrapUpdateSupplierResult("success to update");
        QString info="update   Supplier   ";
        info.append(id);
        info.append("   ");
        info.append(name);
        writeToFile(info);

    }
    sendMessage();
}

void FortuneThread::searchSupplier(const QString id)
{
    QSqlQuery query(db);
    query.prepare("select * from supplier where id = ?");
    query.bindValue(0,id);
    query.exec();
    //default

    result=wrapper->wrapDefaultResult("error:Nothing to show");
    while(query.next()){
        QString value0=query.value(0).toString();//id
        QString value1=query.value(1).toString();//name
        QString value2=query.value(2).toString();//phone
        int value3=query.value(3).toInt();//type

        if(0==id.compare(value0)){
            result=wrapper->wrapSearchSupplierResult(value0,value1,value3,value2);
        }
    }
    sendMessage();
}

void FortuneThread::searchAllSupplier()
{
    QSqlQuery query(db);
    query.prepare("select * from supplier");
    query.exec();

    QJsonArray array;
    QJsonObject carry;

    int count=0;
    result=wrapper->wrapDefaultResult("error:Nothing to show");
    while(query.next()){
        QString value0=query.value(0).toString();//id
        QString value1=query.value(1).toString();//name
        QString value2=query.value(2).toString();//phone
        int value3=query.value(3).toInt();//type

        QJsonObject obj=wrapper->wrapSupplierToJsonObject(value0,value1,value3,value2);
        array.insert(count++,obj);
    }
    carry.insert("suppliers",array);
    result=wrapper->wrapSearchAllSupplierResult(carry);
    sendMessage();
}

void FortuneThread::searchSupplierByType(int type)
{
    QSqlQuery query(db);
    query.prepare("select * from supplier where type = ?");
    query.bindValue(0,type);
    query.exec();

    QJsonArray array;
    QJsonObject carry;

    int count=0;
    result=wrapper->wrapDefaultResult("error:Nothing to show");
    while(query.next()){
        QString value0=query.value(0).toString();//id
        QString value1=query.value(1).toString();//name
        QString value2=query.value(2).toString();//phone
        int value3=query.value(3).toInt();//type

        QJsonObject obj=wrapper->wrapSupplierToJsonObject(value0,value1,value3,value2);
        array.insert(count++,obj);
    }
    carry.insert("suppliers",array);
    result=wrapper->wrapSearchAllSupplierResult(carry);
    sendMessage();
}

void FortuneThread::createVIP(QString id, QString name, QString phone)
{
    QSqlQuery query(db);
    query.exec("select * from vip");
    //default

    result=wrapper->wrapCreateVIPResult("error:already has the id");
    bool hasNoRecord=true;

    while(query.next()){
        QString value0=query.value(0).toString();//uid
        if(hasNoRecord&&0==value0.compare(id)){
            hasNoRecord=false;
            break;
        }

    }
    if(hasNoRecord){
        query.prepare(tr("insert into vip values(?,?,?,?)"));
        query.bindValue(0,id);
        query.bindValue(1,name);
        query.bindValue(2,phone);
        query.bindValue(3,0);

        query.exec();
        qDebug() << query.lastError();
        result=wrapper->wrapSignUpResult("success to create");

        QString info="create VIP ";
        info.append(id);
        writeToFile(info);

    }
    sendMessage();
}

void FortuneThread::deleteVIP(QString id)
{
    QSqlQuery query(db);
    query.exec("select * from vip");
    //default

    result=wrapper->wrapDeleteVIPResult("error:donnot have the id");

    bool hasPerson=false;
    while(query.next()){
        QString value0=query.value(0).toString();//uid
        if(!hasPerson&&0==value0.compare(id)){
            hasPerson=true;
            break;
        }
    }

    if(hasPerson){
        query.clear();
        query.prepare(tr("delete from vip where id = ? "));
        query.bindValue(0,id);
        query.exec();
        qDebug()<<query.lastError();
        result=wrapper->wrapDeleteVIPResult("success to delete");

        QString info="delete VIP ";
        info.append(id);
        writeToFile(info);
    }
    sendMessage();
}

void FortuneThread::updateVIP(QString id, int score,bool ret)
{
    QSqlQuery query(db);
    query.exec("select * from vip");
    //default

    result=wrapper->wrapUpdateVIPResult("error:donot have the vip");

    bool hasRecord=false;
    int hasScore=0;
    while(query.next()){
        QString value0=query.value(0).toString();//uid
        if(!hasRecord&&0==value0.compare(id)){
            hasRecord=true;
            hasScore=query.value(3).toInt();
            break;
        }
    }

    if(hasRecord){
        query.clear();
        query.prepare(tr("update vip set score = ? where id = ? "));
        query.bindValue(0,hasScore+score);
        query.bindValue(1,id);
        query.exec();
        qDebug() << query.lastError();
        result=wrapper->wrapUpdateVIPResult("success to update vip");

        QString info="update VIP ";
        info.append(id);
        writeToFile(info);

    }
    if(ret){
        sendMessage();
    }
}

void FortuneThread::searchVIP(QString id)
{
    QSqlQuery query(db);
    query.prepare("select * from vip where id = ?");
    query.bindValue(0,id);
    query.exec();
    //default

    result=wrapper->wrapDefaultResult("error:donot have the vip ID");
    while(query.next()){
        QString value0=query.value(0).toString();//id
        QString value1=query.value(1).toString();//name
        QString value2=query.value(2).toString();//phone
        int value3=query.value(3).toInt();//score



        if(0==id.compare(value0)){
            result=wrapper->wrapSearchVIPResult(value0,value1,value2,value3);
        }
    }
    sendMessage();

}

void FortuneThread::exchangeVIP(QString id, int score)
{
    QSqlQuery query(db);
    query.exec("select * from vip");
    //default

    result=wrapper->wrapUpdateVIPResult("error : dont have this vip");

    bool hasRecord=false;
    int hasScore=0;
    while(query.next()){
        QString value0=query.value(0).toString();//uid
        if(!hasRecord&&0==value0.compare(id)){
            hasRecord=true;
            hasScore=query.value(3).toInt();
            break;
        }
    }

    if(hasRecord){
        if(hasScore>=score){
            query.clear();
            query.prepare(tr("update vip set score = ? where id = ? "));
            query.bindValue(0,hasScore-score);
            query.bindValue(1,id);
            query.exec();
            qDebug() << query.lastError();
            result=wrapper->wrapExchangeVIPResult("success to update");
        }else{
            result=wrapper->wrapExchangeVIPResult("error:donot have enough score");
        }

        QString info="update VIP ";
        info.append(id);
        writeToFile(info);

    }
    sendMessage();
}

void FortuneThread::sendMessage()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << (quint16)0;
    out << result;


    result="";
    theString="";
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));


    tcpSocket->write(block);
    tcpSocket->flush();

}
