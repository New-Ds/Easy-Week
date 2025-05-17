#include "add_product.h"
#include "ui_add_product.h"

AddProductWindow::AddProductWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddProductWindow)
{
    ui->setupUi(this);
    //connect(ui->add, &QPushButton::clicked, this, &AddProductWindow::on_add_clicked);
}

void AddProductWindow::on_add_clicked()
{
    QString name = ui->In_name->text();
    int proteins = ui->In_proteins->text().toInt();
    int fats = ui->In_fats->text().toInt();
    int carbs = ui->In_carbs->text().toInt();
    int weight = ui->In_weights->text().toInt();
    int cost = ui->In_cost->text().toInt();
    int type = ui->comboBox->currentIndex();

    // Проверка на заполненность полей
    if (name.isEmpty() || ui->In_proteins->text().isEmpty() ||
        ui->In_fats->text().isEmpty() || ui->In_carbs->text().isEmpty() ||
        ui->In_weights->text().isEmpty() || ui->In_cost->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }

    emit productAdded(name, proteins, fats, carbs, weight, cost, type);

    this->clear();
    this->close();
}

// Деструктор
AddProductWindow::~AddProductWindow()
{
    delete ui;
}

void AddProductWindow::clear() {
    ui->In_name->setText("");
    ui->In_proteins->setText("");
    ui->In_fats->setText("");
    ui->In_carbs->setText("");
    ui->In_weights->setText("");
    ui->In_cost->setText("");
    ui->comboBox->setCurrentIndex(-1);
};

// Показывает окно
void AddProductWindow::slot_show()
{
    this->show();

}
