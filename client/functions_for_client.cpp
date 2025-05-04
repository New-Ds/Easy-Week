#include "functions_for_client.h"

#include <QDebug>
#include <QByteArray>
#include <QStringList>


QString auth(QString email, QString password) {

    ClientSingleton& client = ClientSingleton::getInstance();

    QString response = client.send_msg(QStringList{"auth", email, password});

    qDebug() << "Авторизация: " << response;

    return response;
};

bool reg(QString login, QString password, QString email) {

    ClientSingleton& client = ClientSingleton::getInstance();

    QString response = client.send_msg(QStringList{"reg", login, email, password});

    QStringList parts = response.split("//");

    // проверка на успешность регистрации
    if (parts[0] == "reg_success") {
        return true;
    }
    return false;
};

QString get_stable_stat() {

    ClientSingleton& client = ClientSingleton::getInstance();

    QString stat = client.send_msg(QStringList{"admin", "stable_stat"});

    return stat;

};

QString get_dynamic_stat() {

    ClientSingleton& client = ClientSingleton::getInstance();

    QString stat = client.send_msg(QStringList{"admin", "dynamic_stat"});

    return stat;

};


QByteArray get_all_users() {

    ClientSingleton& client = ClientSingleton::getInstance();

    QByteArray stat = client.send_msg(QStringList{"admin", "get_all_users"});

    return stat;
};


QByteArray get_products(QString id) {
    ClientSingleton& client = ClientSingleton::getInstance();

    QStringList params = {"user", id, "get_products"};

    QByteArray response = client.send_msg(params);
    qDebug() << "Сырой ответ от сервера (JSON): " << response;

    return response;  // <-- просто возвращаем JSON байты, пусть парсинг делает кликер
}


