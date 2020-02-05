#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QString>

#define DATABASE_HOSTNAME   "Shop"
#define DATABASE_NAME       "Cement.db"

#define TABLE_CAT               "Categories"
#define TABLE_CAT_NAME          "Cat_Name"
#define TABLE                   "Goods"
#define TABLE_NAME              "Name"
#define TABLE_COUNT             "Count"
#define TABLE_PRICE             "Price"
#define TABLE_DATE              "Date"
#define TABLE_SOLD              "Sold"
#define TABLE_SOLD_NAME         "Sold_Name"
#define TABLE_SOLD_COUNT        "Sold_Count"
#define TABLE_SOLD_MONEY        "Sold_Money"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    void connectToDataBase();
    bool inserIntoTable(const QVariantList &data);
    bool insertIntoCat(const QVariantList &data);
    void fillCat(QString name);

private:
    QSqlDatabase    db;

private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();
};

#endif // DATABASE_H
