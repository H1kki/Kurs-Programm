#include "admincheck.h"
#include "ui_admincheck.h"

sold::sold(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sold)
{
    ui->setupUi(this);

    db = new DataBase();
        db->connectToDataBase();
        this->setupModel(TABLE_SOLD,
                         QStringList() << tr("Назва товару")
                                       << tr("Ціна")
                   );

        this->createUI();
        QSqlQuery query;
        query.prepare("SELECT SUM(" TABLE_SOLD_MONEY ") FROM " TABLE_SOLD);
        query.exec();
        query.next();
        ui->soldLabel->setText(query.value(0).toString());
}

sold::~sold()
{
    delete ui;
}

void sold::createUI()
{
    ui->tableView->setModel(model);
    //ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSortingEnabled(true);
    //ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableView->horizontalHeader()->setStretchLastSection(false);
}

void sold::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    model->setSort(0,Qt::AscendingOrder);
}
