#include "authregwindow.h"
#include "ui_authregwindow.h"

AuthRegWindow::AuthRegWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthRegWindow)
{
    ui->setupUi(this);
    ui->loginLabel->setVisible(false);
    ui->loginLine->setVisible(false);
    change_type_to_reg(false);
}




void AuthRegWindow::change_type_to_reg(bool is_reg) {
    ui->reportMessage->setText("");

    ui->loginLabel->setVisible(is_reg);
    ui->loginLine->setVisible(is_reg);

    ui->confirmPasswordLabel->setVisible(is_reg);
    ui->confirmPasswordLine->setVisible(is_reg);

    ui->regButton->setVisible(is_reg);
    ui->loginButton->setVisible(!is_reg);
    ui->toRegButton->setText(!is_reg? "РЕГИСТРАЦИЯ" : "АВТОРИЗАЦИЯ");
};

AuthRegWindow::~AuthRegWindow()
{
    delete ui;
}

void AuthRegWindow::on_toRegButton_clicked()
{
    change_type_to_reg(!ui->loginLabel->isVisible());
}






void AuthRegWindow::on_loginButton_clicked()
{


    QString response = auth(ui->emailLine->text(), ui->passwordLine->text());

    QStringList parts = response.split("//");

    if (parts[0] == "auth_success") {
        QString id = parts[1];
        QString login = parts[2];
        QString email = parts[3];
        QString password = parts[4];

        emit auth_ok(id, login, email, password);
        this->close();
    }


    else {
        ui->reportMessage->setText("Ошибка, проверьте правильность введённых данных");
        clear();
    }
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
        ui->reportMessage->setText("Введённые пароли не совпадают");
    } else {
        if (reg(ui->loginLine->text(), // делаем запрос на сервер для регистрации, передаём логин, пароль, почту
            ui->passwordLine->text(),
            ui->emailLine->text()))
        {
            ui->loginLine->setText("");
            ui->confirmPasswordLine->setText("");
            ui->reportMessage->setText("Регистрация успешна, нажмите login для авторизации");
            change_type_to_reg(false);
        } else {
            ui->reportMessage->setText("Ошибка, пользователь с таким email уже существует");
            this->clear();
        };
    }
}































