#include "managerforms.h"

ManagerForms::ManagerForms(QWidget *parent)
    : QMainWindow(parent)
{
    this->curr_auth = new AuthRegWindow();
    this->main = new MainWindow();
    this->curr_auth->show();



    connect(curr_auth, &AuthRegWindow::auth_ok, main, &MainWindow::slot_show);
    connect(curr_auth, &AuthRegWindow::auth_ok, main, &MainWindow::set_current_user);
}

ManagerForms::~ManagerForms()
{

}

