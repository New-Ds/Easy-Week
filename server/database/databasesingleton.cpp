#include "databasesingleton.h"
#include "migrations.h"

DataBaseSingleton* DataBaseSingleton::p_instance = nullptr;
SingletonDestroyer DataBaseSingleton::destroyer;

DataBaseSingleton::DataBaseSingleton() {
    db = QSqlDatabase::addDatabase("QSQLITE");
}

DataBaseSingleton* DataBaseSingleton::getInstance() {
    if (!p_instance) {
        p_instance = new DataBaseSingleton();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

bool DataBaseSingleton::initialize(const QString& databaseName) {
    db.setDatabaseName(databaseName);
    if (!db.open()) {
        qDebug() << "Ошибка подключения:" << db.lastError().text();
        return false;
    }

    // Выполнение миграций для создания необходимых таблиц
    return Migrations::runMigrations(db);
}

QSqlQuery DataBaseSingleton::executeQuery(const QString& queryStr, const QVariantMap& params) {
    QSqlQuery query(db);
    query.prepare(queryStr);
    for (auto it = params.begin(); it != params.end(); ++it) {
        query.bindValue(it.key(), it.value());
    }
    if (!query.exec()) {
        qDebug() << "Ошибка запроса:" << query.lastError().text();
        qDebug() << "Текст запроса:" << queryStr;
    }
    return query;
}

// Методы для работы с таблицей users
bool DataBaseSingleton::checkUserCredentials(const QString& email, const QString& password) {
    QSqlQuery query = executeQuery(
        "SELECT * FROM users WHERE email = :email AND pass = :pass",
        {{":email", email}, {":pass", password}}
        );
    return query.next();
}

bool DataBaseSingleton::addUser(const QString& name, const QString& email, const QString& password, bool isAdmin) {
    QSqlQuery query = executeQuery(
        "INSERT INTO users (name, email, pass, is_admin) VALUES (:name, :email, :pass, :is_admin)",
        {{":name", name}, {":email", email}, {":pass", password}, {":is_admin", isAdmin}}
        );

    if (query.lastError().isValid()) {
        qDebug() << "Ошибка SQL:" << query.lastError().text();
        return false;
    }
    return true;
}

// Методы для работы с таблицей products
bool DataBaseSingleton::addProduct(int userId, const QString& name, int proteins, int fatness, int carbs, int weight, int cost, int type) {
    QSqlQuery query = executeQuery(
        "INSERT INTO products (id_user, name, proteins, fatness, carbs, weight, cost, type) "
        "VALUES (:id_user, :name, :proteins, :fatness, :carbs, :weight, :cost, :type)",
        {
            {":id_user", userId},
            {":name", name},
            {":proteins", proteins},
            {":fatness", fatness},
            {":carbs", carbs},
            {":weight", weight},
            {":cost", cost},
            {":type", type}
        }
        );
    return !query.lastError().isValid(); // Возвращаем true, если ошибок нет
}

QVector<QVariantMap> DataBaseSingleton::getProductsByUser(int userId) {
    QSqlQuery query = executeQuery(
        "SELECT * FROM products WHERE id_user = :id_user",
        {{":id_user", userId}}
        );
    QVector<QVariantMap> products;
    while (query.next()) {
        QVariantMap product;
        product["id"] = query.value("id").toInt();
        product["name"] = query.value("name").toString();
        product["proteins"] = query.value("proteins").toInt();
        product["fatness"] = query.value("fatness").toInt();
        product["carbs"] = query.value("carbs").toInt();
        product["weight"] = query.value("weight").toInt();
        product["cost"] = query.value("cost").toInt();
        product["type"] = query.value("type").toInt();
        products.append(product);
    }
    return products;
}

// Методы для работы с таблицей favorites
bool DataBaseSingleton::addFavoriteRation(int userId, const QVector<int>& productIds, int calories, int allCost, int allWeight) {
    // Преобразуем QVector<int> в QVector<QString>
    QVector<QString> productIdsStr;
    for (int id : productIds) {
        productIdsStr.append(QString::number(id)); // Преобразуем int в QString
    }

    // Преобразуем QVector<QString> в QStringList и объединяем в строку через запятую
    QString productsStr = QStringList::fromVector(productIdsStr).join(",");

    // Выполняем SQL-запрос
    return executeQuery(
               "INSERT INTO favorites (id_user, products, calories, all_cost, all_weight) "
               "VALUES (:id_user, :products, :calories, :all_cost, :all_weight)",
               {{":id_user", userId}, {":products", productsStr}, {":calories", calories},
                {":all_cost", allCost}, {":all_weight", allWeight}}
               ).exec();
}

QVector<QVariantMap> DataBaseSingleton::getFavoritesByUser(int userId) {
    QSqlQuery query = executeQuery(
        "SELECT * FROM favorites WHERE id_user = :id_user",
        {{":id_user", userId}}
        );
    QVector<QVariantMap> favorites;
    while (query.next()) {
        QVariantMap favorite;
        favorite["products"] = query.value("products").toString();
        favorite["calories"] = query.value("calories").toInt();
        favorite["all_cost"] = query.value("all_cost").toInt();
        favorite["all_weight"] = query.value("all_weight").toInt();
        favorites.append(favorite);
    }
    return favorites;
}

// Методы для работы с таблицей statistics
bool DataBaseSingleton::updateStatistics(int registrations, int visits, int generations) {
    return executeQuery(
               "UPDATE statistics SET count_registrations = :registrations, "
               "count_visits = :visits, count_generations = :generations",
               {{":registrations", registrations}, {":visits", visits}, {":generations", generations}}
               ).exec();
}

QVariantMap DataBaseSingleton::getStatistics() {
    QSqlQuery query = executeQuery("SELECT * FROM statistics");
    QVariantMap stats;
    if (query.next()) {
        stats["registrations"] = query.value("count_registrations").toInt();
        stats["visits"] = query.value("count_visits").toInt();
        stats["generations"] = query.value("count_generations").toInt();
    }
    return stats;
}

// Реализация разрушителя
SingletonDestroyer::~SingletonDestroyer() { delete p_instance; }
void SingletonDestroyer::initialize(DataBaseSingleton* p) { p_instance = p; }