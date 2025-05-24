#include "managerforms.h"

ManagerForms::ManagerForms(QWidget *parent) : QMainWindow(parent)
{
    this->curr_auth = new AuthRegWindow();
    this->main = new MainWindow();
    this->curr_auth->show();
    this->addProductWindow = new AddProductWindow();

    // Связываем сигналы и слоты для переключения между окнами
    connect(main, &MainWindow::add_product, addProductWindow, &AddProductWindow::slot_show);
    connect(addProductWindow, &AddProductWindow::productAdded, main, &MainWindow::handleProductAdded);

    connect(curr_auth, &AuthRegWindow::auth_ok, main, &MainWindow::slot_show);
    connect(curr_auth, &AuthRegWindow::auth_ok, main, &MainWindow::set_current_user);
}

ManagerForms::~ManagerForms()
{
    // Qt автоматически удалит дочерние объекты
}