#include "userwindow.h"
#include "ui_userwindow.h"

userWindow::userWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userWindow)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();


    this->setupModel(TABLE,
                     QStringList() << tr("id")
                                   << tr("Назва товару")
                                   << tr("Ціна")
                                   << tr("Кількість")
                                   << tr("Категорія")
                                   << tr("Дата добавлення")
               );

    this->createUI();
}

userWindow::~userWindow()
{
    delete ui;
}

void userWindow::createUI()
{
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setStretchLastSection(false);


    slotUpdateModels();
}

void userWindow::slotUpdateModels()
{
    model->select();
}

void userWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    model->setSort(0,Qt::AscendingOrder);
}

void userWindow::on_pushButton_clicked()
{
    query = new QSqlQuery;

    QString id = model->data(model->index(ui->tableView->currentIndex().row(), 0)).toString();
    QString name = model->data(model->index(ui->tableView->currentIndex().row(), 1)).toString();
    QString price = model->data(model->index(ui->tableView->currentIndex().row(), 2)).toString();

    int selectedRow = ui->tableView->currentIndex().row();
    int count = model->data(model->index(ui->tableView->currentIndex().row(), 3)).toInt();

    if (selectedRow >=0){
        if(count > 1){
                query->prepare("UPDATE Goods SET Count = Count-1 WHERE id = " + id);
                query->exec();
                query->prepare("INSERT INTO Sold(Sold_Name,Sold_Money) VALUES('"+name+"','"+price+"')");
                if(!query->exec()){
                    qDebug() << "error insert into " << TABLE_SOLD;
                    qDebug() << query->lastError().text();
                }
        }
        else {
            model->removeRow(selectedRow);
        model->submitAll();
        }
    }
    createUI();
}
