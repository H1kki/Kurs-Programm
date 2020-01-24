#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include "database.h"
#include <QtSql/QSqlTableModel>

namespace Ui {
class userWindow;
}

class userWindow : public QWidget
{
    Q_OBJECT

public:
    explicit userWindow(QWidget *parent = nullptr);
    ~userWindow();

private slots:
    void slotUpdateModels();

    void on_pushButton_clicked();

private:
    Ui::userWindow *ui;
    DataBase        *db;
    QSqlTableModel  *model;
    QSqlQuery *query;
    QSqlQueryModel *querymodel;

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};


#endif // USERWINDOW_H
