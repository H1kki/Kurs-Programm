#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

//Підключення до бази даних
void DataBase::connectToDataBase()
{
    if(!QFile(DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

//Відновлення бази даних
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не вдалося відновити базу даних";
        return false;
    }
    return false;
}

//Створення або відкриття бази
bool DataBase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void DataBase::closeDataBase()
{
    db.close();
}

//Створення таблиць
bool DataBase::createTable()
{
    QSqlQuery query;

    //Таблиця товарів
    if(!query.exec( "CREATE TABLE " TABLE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                            TABLE_NAME      " VARCHAR(255)      NOT NULL,"
                            TABLE_PRICE     " DOUBLE            NOT NULL,"
                            TABLE_COUNT     " INTEGER           NOT NULL,"
                            TABLE_CAT_NAME  " VARCHAR(255)      NOT NULL,"
                            TABLE_DATE      " DATE              NOT NULL"
                    " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return  false;
    }
        //Таблиця категорій
        if(!query.exec( "CREATE TABLE " TABLE_CAT " ("
                       TABLE_CAT_NAME  " VARCHAR(255)                       NOT NULL"
                   " ) "
                        )){
            qDebug() << "DataBase: error of create " << TABLE_CAT;
            qDebug() << query.lastError().text();
        return false;
    }
         //Таблиця куплених товарів
        if(!query.exec("CREATE TABLE " TABLE_SOLD " ("
                       TABLE_SOLD_NAME          " VARCHAR(255)      NOT NULL,"
                       TABLE_SOLD_MONEY         " DOUBLE            NOT NULL"
                       " )"
                       )){
            qDebug() << "DataBase: error of create " << TABLE_SOLD;
            qDebug() << query.lastError().text();
        }

        else {
        return true;
    }
    return false;
}

//Вставка даних в таблицю з товарами
bool DataBase::inserIntoTable(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE " ( " TABLE_NAME ", "
                                             TABLE_PRICE ", "
                                             TABLE_COUNT ", "
                                             TABLE_CAT_NAME ", "
                                             TABLE_DATE " ) "
                  "VALUES (:Name, :Price, :Count, :Cat, :Date)");
    query.bindValue(":Name",       data[0].toString());
    query.bindValue(":Price",      data[1].toDouble());
    query.bindValue(":Count",      data[2].toInt());
    query.bindValue(":Cat",      data[3].toString());
    query.bindValue(":Date",       data[4].toDate());
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

//Вставка даних в таблицю з категоріями
bool DataBase::insertIntoCat(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE_CAT " ( " TABLE_CAT_NAME " ) "
                  "VALUES (:Name)");
    query.bindValue(":Name",        data[0].toString());
    if(!query.exec()){
        qDebug() << "error insert into" << TABLE_CAT;
        qDebug() << query.lastError().text();
        return  false;
    } else {
            return true;
    }
}

//Заповення таблиці категорій
void DataBase::fillCat(QString name)
{
    QSqlQuery query("SELECT Cat_Name FROM Categories where Cat_Name='" + name + "'");
            query.first();
    if(query.value(0).toString()==""){
    QVariantList data;

    data.append(name);
    insertIntoCat(data);
    data.clear();
}
}
