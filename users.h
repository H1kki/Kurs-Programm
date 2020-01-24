#ifndef USERS_H
#define USERS_H

#include <QWidget>
#include "loginwindow.h"
#include "userwindow.h"

namespace Ui {
class users;
}

class users : public QWidget
{
    Q_OBJECT

public:
    explicit users(QWidget *parent = nullptr);
    ~users();

private slots:
    void on_adminButton_clicked();

    void on_userButton_clicked();

private:
    Ui::users *ui;
    loginWindow *login;
};

#endif // USERS_H
