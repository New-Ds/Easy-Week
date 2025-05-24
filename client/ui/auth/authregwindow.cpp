#include "authregwindow.h"
#include "ui_authregwindow.h"
#include "../../services/authservice.h"

AuthRegWindow::AuthRegWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthRegWindow)
{
    ui->setupUi(this);
    ui->loginLabel->setVisible(false);
    ui->loginLine->setVisible(false);
    changeTypeToReg(false);

    this->setFixedSize(this->width(), this->height());
}

void AuthRegWindow::changeTypeToReg(bool isReg) {
    ui->reportMessage->setText("");

    ui->loginLabel->setVisible(isReg);
    ui->loginLine->setVisible(isReg);

    ui->confirmPasswordLabel->setVisible(isReg);
    ui->confirmPasswordLine->setVisible(isReg);

    ui->regButton->setVisible(isReg);
    ui->loginButton->setVisible(!isReg);
    ui->toRegButton->setText(!isReg? "РЕГИСТРАЦИЯ" : "АВТОРИЗАЦИЯ");
};

AuthRegWindow::~AuthRegWindow()
{
    delete ui;
}

void AuthRegWindow::on_toRegButton_clicked()
{
    changeTypeToReg(!ui->loginLabel->isVisible());
}

void AuthRegWindow::on_loginButton_clicked()
{
    QString response = AuthService::authenticate(ui->emailLine->text(), ui->passwordLine->text());
    QStringList parts = response.split("//");

    if (parts[0] == "auth_success") {
        QString id = parts[1];
        QString login = parts[2];
        QString email = parts[3];

        emit auth_ok(id, login, email);
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
        if (AuthService::registerUser(
                ui->loginLine->text(), 
                ui->passwordLine->text(),
                ui->emailLine->text()))
        {
            ui->loginLine->setText("");
            ui->confirmPasswordLine->setText("");
            ui->reportMessage->setText("Регистрация успешна, нажмите login для авторизации");
            changeTypeToReg(false);
        } else {
            ui->reportMessage->setText("Ошибка, пользователь с таким email уже существует");
            this->clear();
        };
    }
}