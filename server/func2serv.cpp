#include "func2serv.h"
#include <QString>
#include <QStringList>
#include <QMap>
#include <QDebug>
#include<databasesingleton.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
// Заглушка для базы данных

QMap<QString, QList<QString>> mockDatabase = {
    {"1", {"orange_11_45_12_24", "banana_11_45_12_24", "orange_11_45_12_24", "orange_11_45_12_24", "orange_11_45_12_24", "orange_11_45_12_24", "orange_11_45_12_24", "orange_11_45_12_24"}},
    {"2", {"apple_11_45_12_24", "grape_11_45_12_24"}}
    };

using namespace std;
QByteArray parsing(QString input, int socdes)
{

    QStringList container = input.remove("\r\n").split("//"); //пример входящих данных reg//login_user//password_user

    if (container.isEmpty()) {
        return "server error: empty command\\n";
    }


    qDebug() << socdes << " user command: " << container[0];
    QString var = container[0];
    if (var == "check_task")
    {
        return check_task();
    }
    else if (var =="auth")
    {
        return auth(container);
    }
    else if (var == "add_product")
    {
        return add_product(container);
    }
    else if (var == "user" && container[2] == "get_products") {
        return get_products(container[1]);
    }
    else if (var =="reg")
    {
        return reg(container);
    }
    else if (var == "get_stat")
    {
        return(get_stat());
    }
    else if (var == "admin" && container[1] == "dynamic_stat") {
        return get_dynamic_stat();
    }
    else if (var == "menu_export")
    {
        return menu_export();
    }
    else if (var == "user" && container[2] == "add_favorite_ration") {
        return add_favorite_ration(container);
    }
    else if (var == "admin" && container[1] == "get_all_users") {
        return get_all_users();
    }
    else if (var == "admin" && container[1] == "stable_stat") {
        return get_stable_stat();
    }
    else
    {
        return "server error: unknow command\r\n";
    }
}


// дарова Руслан, когда будешь писать тут функцию эту, при успешной авторизации просто пропиши return "true", при неуспешной return "false", на клиенте я так принимаю ответ
QByteArray auth(QStringList log) {
    // Проверяем количество параметров
    if (log.size() < 3) {
        return "auth_failed//Недостаточно параметров для авторизации\r\n";
    }

    DataBaseSingleton* db = DataBaseSingleton::getInstance();
    bool authSuccess = db->checkUserCredentials(log[1], log[2]);

    if (!authSuccess) {
        return "auth_failed//Неверный логин или пароль\r\n";
    }



    QSqlQuery query = db->executeQuery(
        "SELECT id, name, email, pass FROM users WHERE (email = :login OR name = :login) AND pass = :pass",
        {
            {":login", log[1]}, // логин
            {":pass", log[2]}   // пароль
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


QByteArray reg(QStringList params) {
    // 1️⃣ Проверка количества параметров
    if (params.size() != 4) {
        return "reg_failed//Недостаточно параметров для регистрации\r\n";
    }

    // 2️⃣ Извлечение данных из запроса
    QString name = params[1];      // Имя пользователя
    QString email = params[2];     // Email (должен быть уникальным)
    QString password = params[3];  // Пароль

    DataBaseSingleton* db = DataBaseSingleton::getInstance();

    // 3️⃣ Проверка, не занят ли email
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

    // 4️⃣ Попытка добавить пользователя
    bool success = db->addUser(name, email, password, false);

    if (success) {
        // 5️⃣ Обновление статистики (увеличиваем счетчик регистраций)
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

QByteArray add_product(QStringList params) {
    if (params.size() != 9) {
        return "add_product//failed//Неверные аргументы\r\n";
    }

    DataBaseSingleton *db = DataBaseSingleton::getInstance();
    int userId = params[1].toInt();
    QString name = params[2];
/*
    // Проверяем, существует ли уже такой продукт
    QSqlQuery checkQuery = db->executeQuery(
        "SELECT id FROM products WHERE id_user = :id_user AND name = :name",
        {{":id_user", userId}, {":name", name}}
        );

    if (checkQuery.next()) {
        return "add_product//failed//Продукт уже существует\r\n";
    }
*/
    // Добавляем продукт
    bool success = db->addProduct(
        userId,
        name,
        params[3].toInt(), // proteins
        params[4].toInt(), // fatness
        params[5].toInt(), // carbs
        params[6].toInt(), // weight
        params[7].toInt(), // cost
        params[8].toInt()  // type
        );

    return success ? "add_product//success\r\n" : "add_product//failed//Ошибка БД\r\n";
}

QByteArray get_stat(/*QStringList*/){
    return "Your Statistic: null\r\n";
}

QByteArray check_task(/*QStringList*/){
    return "Task was succesful completed\r\n";
}
QByteArray menu_export(/*QStringList*/){
    return "Меню успешно экспортировано!\r\n";
}

void fetch_products_from_db(const QString& userId, QStringList& products) {

    if (mockDatabase.contains(userId)) {
        products = mockDatabase[userId];
    }
}
QByteArray get_products(QString userId) {
    DataBaseSingleton* db = DataBaseSingleton::getInstance();
    int userIdInt = userId.toInt();
    QVector<QVariantMap> products = db->getProductsByUser(userIdInt);

    QJsonArray jsonArray;
    for (const QVariantMap& product : products) {
        QJsonObject obj = QJsonObject::fromVariantMap(product);
        jsonArray.append(obj);
    }

    QJsonDocument doc(jsonArray);
    QByteArray jsonBytes = doc.toJson(QJsonDocument::Compact);

    qDebug() << "Отправляем продукты в виде JSON:" << jsonBytes;

    return jsonBytes;
}

QByteArray get_all_users() {
    QStringList users;

    // fetch_users_from_db(users);

    QString response;
    for (const QString& user : users) {
        response += user + "\r\n";
    }

    return response.toUtf8();
}
int get_user_count() {
    // Здесь будет SQL-запрос, пока заглушка
    return 152; // Примерное значение
}

int get_product_count() {
    // Здесь будет SQL-запрос, пока заглушка
    return 732; // Примерное значение
}
QByteArray get_stable_stat() {

    int userCount = 0;
    int productCount = 0;

    userCount = get_user_count();
    productCount = get_product_count();

    // Формируем строку ответа
    QString response = "Users: " + QString::number(userCount) + "\r\n" +
                       "Products: " + QString::number(productCount) + "\r\n";

    return response.toUtf8();
}
int get_weekly_logins() {
    // Заглушка, пока без БД
    return 78; // Примерное значение
}

int get_monthly_logins() {
    // Заглушка, пока без БД
    return 312; // Примерное значение
}
QByteArray get_dynamic_stat() {
    int weeklyLogins = 0;
    int monthlyLogins = 0;

    // Получаем данные из БД (пока заглушки)
    weeklyLogins = get_weekly_logins();
    monthlyLogins = get_monthly_logins();

    // Формируем строку ответа
    QString response = "Logins per week: " + QString::number(weeklyLogins) + "\r\n" +
                       "Logins per month: " + QString::number(monthlyLogins) + "\r\n";

    return response.toUtf8();
}
QByteArray add_favorite_ration(const QStringList& container) {
    QString userId = container[1]; // ID пользователя
    QString rationId = container[2]; // ID рациона

    bool success = add_ration_to_favorites(userId, rationId); // Вызов функции-заглушки

    if (success) {
        return "Ration successfully added to favorites\r\n";
    } else {
        return "Error: failed to add ration to favorites\r\n";
    }
}
bool add_ration_to_favorites(const QString& userId, const QString& rationId) {
    qDebug() << "Adding ration for user:" << userId << ", ration ID:" << rationId;
    return true; // Заглушка, потом заменить на SQL-запрос
}








