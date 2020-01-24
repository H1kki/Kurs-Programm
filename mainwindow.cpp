#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();
    db->fillCat("Будматеріали");
    db->fillCat("Інструменти");
    db->fillCat("Оздоблювальні матеріали");
    db->fillCat("Вікна і двері");
    db->fillCat("Клеї і суміші");
    db->fillCat("Штукатурки і грунтовки");


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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    model->setSort(0,Qt::AscendingOrder);
}

void MainWindow::createUI()
{
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView->resizeColumnToContents(1);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableView->horizontalHeader()->setStretchLastSection(false);


    slotUpdateModels();
}

//Запис данних в базу
void MainWindow::on_insertData_clicked()
{
    insertData *initData = new insertData;
    connect(initData, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    initData->setWindowTitle("Cement");
    initData->exec();
}

//Видалення записів з бази данних
void MainWindow::on_deleteData_clicked()
{
    ui->deleteData->setEnabled(false);
    int selectedRow = ui->tableView->currentIndex().row();
    if (selectedRow >=0)
        model->removeRow(selectedRow);
    model->submitAll();
    createUI();
}

void MainWindow::on_tableView_clicked()
{
    ui->deleteData->setEnabled(true);
}

//Слот для оновлення данних в таблиці
void MainWindow::slotUpdateModels()
{
    model->select();
}

void MainWindow::on_soldGoods_clicked()
{
    sold *s = new sold;

    s->setWindowTitle("Cement");
    s->show();
}
