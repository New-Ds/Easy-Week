#include "authregwindow.h"
#include "ui_authregwindow.h"

//bool isAuth = auth("admin", "root");

AuthRegWindow::AuthRegWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthRegWindow)
{
    ui->setupUi(this);
    change_type_to_reg(false);
}




void AuthRegWindow::change_type_to_reg(bool is_reg) {
    ui->confirmPasswordLabel->setVisible(is_reg);
    ui->emailLabel->setVisible(is_reg);
    ui->confirmPasswordLine->setVisible(is_reg);
    ui->emailLine->setVisible(is_reg);
    ui->regButton->setVisible(is_reg);

    ui->loginButton->setVisible(!is_reg);
    ui->toRegButton->setText(!is_reg? "to Reg" : "to Auth");
};

AuthRegWindow::~AuthRegWindow()
{
    delete ui;
}

void AuthRegWindow::on_toRegButton_clicked()
{
    change_type_to_reg(!ui->emailLabel->isVisible());
}






void AuthRegWindow::on_loginButton_clicked()
{
    if (auth(ui->loginLine->text(), ui->passwordLine->text()) )
    {
        emit auth_ok(ui->loginLine->text(), ui->passwordLine->text(), ui->emailLine->text());
        this->close();
    }
    else { clear(); }
}

void AuthRegWindow::clear() {
    ui->loginLine->setText("");
    ui->emailLine->setText("");
    ui->passwordLine->setText("");
    ui->confirmPasswordLine->setText("");
};


void AuthRegWindow::on_regButton_clicked()
{
    if (ui->passwordLine->text() != ui->confirmPasswordLine->text()) {
        this->clear();
    } else {
        if (reg(ui->loginLine->text(), // делаем запрос на сервер для регистрации, передаём логин, пароль, почту
            ui->passwordLine->text(),
            ui->emailLine->text()))
        {
            emit auth_ok(ui->loginLine->text(), ui->passwordLine->text(), ui->emailLine->text()); //если регистрация успешна, отправляем сигнал что авторизация успешна
            this->close();
        } else {
            this->clear();
        };
    }
}































