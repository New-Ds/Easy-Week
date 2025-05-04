#include "add_product.h"
#include "ui_add_product.h"

AddProductWindow::AddProductWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddProductWindow)
{
    ui->setupUi(this);
}

AddProductWindow::~AddProductWindow()
{
    delete ui;
}

void AddProductWindow::slot_show() {
    this->show();
};
