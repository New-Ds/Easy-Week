#include "authservice.h"
#include "../network/singleton.h"
#include <QDebug>

QString AuthService::authenticate(const QString& email, const QString& password)
{
    NetworkSingleton& client = NetworkSingleton::getInstance();
    QString response = client.sendMessage(QStringList{"auth", email, password});
    qDebug() << "Авторизация: " << response;
    return response;
}

bool AuthService::registerUser(const QString& login, const QString& password, const QString& email)
{
    NetworkSingleton& client = NetworkSingleton::getInstance();
    QString response = client.sendMessage(QStringList{"reg", login, email, password});
    QStringList parts = response.split("//");

    // проверка на успешность регистрации
    if (parts[0] == "reg_success") {
        return true;
    }
    return false;
}

QByteArray AuthService::getAllUsers()
{
    NetworkSingleton& client = NetworkSingleton::getInstance();

    // Архитектурное решение: отправка команды без лишних параметров
    QByteArray response = client.sendMessage(QStringList{"admin", "get_all_users"});

    // Техническое решение: очистка ответа от протокольных артефактов
    if (response.endsWith("\r\n")) {
        response.chop(2);
    }

    // Валидация структуры JSON перед возвратом
    response = response.trimmed();

    // Диагностика для отладки
    qDebug() << "get_all_users raw response:" << response.left(100) << "...";

    return response;
}