#include "loginwindow.h"
#include "ui_loginwindow.h"

loginWindow::loginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
}

loginWindow::~loginWindow()
{
    delete ui;

}

bool loginWindow::checkLog()
{
    if(ui->pass->text() == "admin" && ui->login->text() == "admin"){
        return true;
    }
    else
    {
        QMessageBox::about(this,"Error","Неправильний пароль або логін");
        return false;
    }
}

void loginWindow::on_signIn_clicked()
{
    if(checkLog()){
        MainWindow *adminWindow = new MainWindow;
        adminWindow->setWindowTitle("Cement");
        adminWindow->show();
        this->close();
    }
}
