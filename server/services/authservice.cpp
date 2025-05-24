#include "authservice.h"
#include "../database/databasesingleton.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QSqlQuery>

AuthService::AuthService(QObject *parent) : QObject(parent)
{
}

QByteArray AuthService::authenticateUser(const QStringList& params)
{
    // Проверяем количество параметров
    if (params.size() < 3) {
        return "auth_failed//Недостаточно параметров для авторизации\r\n";
    }

    DataBaseSingleton* db = DataBaseSingleton::getInstance();
    bool authSuccess = db->checkUserCredentials(params[1], params[2]);

    if (!authSuccess) {
        return "auth_failed//Неверный логин или пароль\r\n";
    }

    QSqlQuery query = db->executeQuery(
        "SELECT id, name, email, pass FROM users WHERE (email = :login OR name = :login) AND pass = :pass",
        {
            {":login", params[1]}, // логин
            {":pass", params[2]}   // пароль
        }
        );

    if (!query.next()) {
        return "auth_failed//Ошибка при получении данных пользователя\r\n";
    }

    QString userId = query.value("id").toString();
    QString userLogin = query.value("name").toString();
    QString userEmail = query.value("email").toString();

    QString response = QString("auth_success//%1//%2//%3\r\n")
                           .arg(userId)
                           .arg(userLogin)
                           .arg(userEmail);

    return response.toUtf8();
}

QByteArray AuthService::registerUser(const QStringList& params)
{
    // Проверка количества параметров
    if (params.size() != 4) {
        return "reg_failed//Недостаточно параметров для регистрации\r\n";
    }

    // Извлечение данных из запроса
    QString name = params[1];      // Имя пользователя
    QString email = params[2];     // Email (должен быть уникальным)
    QString password = params[3];  // Пароль

    DataBaseSingleton* db = DataBaseSingleton::getInstance();

    // Проверка, не занят ли email
    QSqlQuery checkQuery = db->executeQuery(
        "SELECT id FROM users WHERE email = :email",
        {{":email", email}}
        );

    // Если запрос не выполнился (ошибка БД)
    if (!checkQuery.exec()) {
        return "reg_failed//Ошибка при проверке email\r\n";
    }

    // Если email уже существует (найдена запись)
    if (checkQuery.next()) {
        return "reg_failed//Пользователь с таким email уже зарегистрирован\r\n";
    }

    // Попытка добавить пользователя
    bool success = db->addUser(name, email, password, false);

    if (success) {
        // Обновление статистики (увеличиваем счетчик регистраций)
        QVariantMap stats = db->getStatistics();
        db->updateStatistics(
            stats["registrations"].toInt() + 1,  // +1 новая регистрация
            stats["visits"].toInt(),            // Визиты без изменений
            stats["generations"].toInt()        // Генерации без изменений
            );
        return "reg_success//Регистрация прошла успешно\r\n";
    } else {
        // Если INSERT не сработал (например, из-за UNIQUE INDEX)
        return "reg_failed//Ошибка при регистрации (возможно, email уже занят)\r\n";
    }
}

QByteArray AuthService::getAllUsers()
{
    qDebug() << "\n=== EXECUTING GET_ALL_USERS ===";

    // Техническое решение: early return паттерн для минимизации задержек
    DataBaseSingleton* db = DataBaseSingleton::getInstance();
    if (!db) {
        qDebug() << "CRITICAL: Database not initialized";
        return "[]";
    }

    // Архитектурное решение: единственный SQL запрос без дополнительных проверок
    QSqlQuery query = db->executeQuery(
        "SELECT id, name, email, is_admin FROM users ORDER BY id"
        );

    // Быстрая проверка на ошибки SQL
    if (query.lastError().isValid()) {
        qDebug() << "SQL Error:" << query.lastError().text();
        return "[]";
    }

    // Оптимизация: резервирование памяти для JSON
    QJsonArray usersArray;

    while (query.next()) {
        QJsonObject userObj;
        userObj["id"] = query.value(0).toInt();
        userObj["name"] = query.value(1).toString();
        userObj["email"] = query.value(2).toString();
        userObj["is_admin"] = query.value(3).toBool();

        usersArray.append(userObj);
    }

    qDebug() << "Users found:" << usersArray.size();

    // Критически важно: компактная сериализация для минимизации размера
    QJsonDocument doc(usersArray);
    QByteArray result = doc.toJson(QJsonDocument::Compact);

    qDebug() << "JSON generated, size:" << result.size();
    qDebug() << "=== GET_ALL_USERS COMPLETE ===\n";

    return result;
}