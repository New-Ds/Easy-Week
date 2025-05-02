#include "functions_for_client.h"

#include <QDebug>
#include <QByteArray>
#include <QStringList>


bool auth(QString login, QString password) {

    ClientSingleton& client = ClientSingleton::getInstance();

    QString response = client.send_msg(QStringList{"auth", login, password});

    qDebug() << "Успешность авторизации: " << response;

    // здесь проверка успешна ли авторизация
    if (response == "true") {
        return true;
    }
    return false;
};

bool reg(QString login, QString password, QString email) {

    ClientSingleton& client = ClientSingleton::getInstance();

    QString response = client.send_msg(QStringList{"reg", login, email, password});


    // проверка на успешность регистрации
    if (response == "true") {
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


QByteArray get_products(QString userId) {

    ClientSingleton& client = ClientSingleton::getInstance();

    // Формируем правильный запрос, который сервер ждёт: user//<userId>//get_products
    QStringList params = {"user", userId, "get_products"};

    QByteArray response = client.send_msg(params);

    return response;
}
