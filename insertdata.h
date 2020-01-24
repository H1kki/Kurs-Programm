#ifndef INSERTDATA_H
#define INSERTDATA_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlField>
#include "database.h"

namespace Ui {
class insertData;
}

class insertData : public QDialog
{
    Q_OBJECT

public:
    explicit insertData(QWidget *parent = nullptr);
    ~insertData();

signals:
    void signalReady();

private slots:
    void on_insert_clicked();


    void on_category_currentIndexChanged();

private:
    Ui::insertData *ui;
    DataBase *db;
    QSqlTableModel *model;
    QSqlQueryModel *queryModel;
    QSqlQuery *query;
    QVariantList *data;

private:
    void setupModel();
    void createUI();
    void addRow();
};

#endif // INSERTDATA_H
