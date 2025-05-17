#ifndef MANAGERFORMS_H
#define MANAGERFORMS_H

#include <QMainWindow>
#include "add_product.h"
#include "authregwindow.h"
#include "mainwindow.h"
#include "Singleton.h"

namespace Ui {
    class ManagerForms;
}

class ManagerForms : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerForms(QWidget *parent = nullptr);
    ~ManagerForms();

private:
    AuthRegWindow * curr_auth;
    MainWindow * main;
    AddProductWindow * addProductWindow;
};


#endif // MANAGERFORMS_H
