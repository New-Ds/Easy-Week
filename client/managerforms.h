#ifndef MANAGERFORMS_H
#define MANAGERFORMS_H

#include <QMainWindow>
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
};


#endif // MANAGERFORMS_H
