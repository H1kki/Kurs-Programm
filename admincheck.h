#ifndef SOLD_H
#define SOLD_H

#include <QWidget>
#include <database.h>
#include <QSqlTableModel>

namespace Ui {
class sold;
}

class sold : public QWidget
{
    Q_OBJECT

public:
    explicit sold(QWidget *parent = nullptr);
    ~sold();

private:
    Ui::sold *ui;
    DataBase        *db;
    QSqlTableModel  *model;
        void setupModel(const QString &tableName, const QStringList &headers);
        void createUI();
};

#endif // SOLD_H
