#include "migrations.h"

bool Migrations::runMigrations(QSqlDatabase& db) {
    if (!createTables(db)) {
        qDebug() << "Ошибка создания таблиц";
        return false;
    }
    
    if (!seedInitialData(db)) {
        qDebug() << "Ошибка инициализации данных";
        return false;
    }
    
    return true;
}

bool Migrations::createTables(QSqlDatabase& db) {
    QSqlQuery query(db);
    bool success = true;
    
    // Создание таблицы users
    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name VARCHAR(20) NOT NULL, "
        "email VARCHAR(50) NOT NULL , "
        "pass VARCHAR(20) NOT NULL, "
        "is_admin BOOLEAN DEFAULT FALSE)"
        );

    success &= query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx_users_email ON users(email)");

    // Создание таблицы products
    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS products ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "id_user INTEGER NOT NULL, "
        "name VARCHAR(50) NOT NULL, "
        "proteins INTEGER NOT NULL, "
        "fatness INTEGER NOT NULL, "
        "carbs INTEGER NOT NULL, "
        "weight INTEGER NOT NULL, "
        "cost INTEGER NOT NULL, "
        "type INTEGER NOT NULL, "
        "FOREIGN KEY(id_user) REFERENCES users(id))"
        );

    // Создание таблицы favorites
    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS favorites ("
        "id_user INTEGER NOT NULL, "
        "products TEXT NOT NULL, "  // Хранение массива ID продуктов в виде строки
        "calories INTEGER NOT NULL, "
        "all_cost INTEGER NOT NULL, "
        "all_weight INTEGER NOT NULL, "
        "FOREIGN KEY(id_user) REFERENCES users(id))"
        );

    // Создание таблицы statistics
    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS statistics ("
        "count_registrations INTEGER DEFAULT 0, "
        "count_visits INTEGER DEFAULT 0, "
        "count_generations INTEGER DEFAULT 0)"
        );
        
    return success;
}

bool Migrations::seedInitialData(QSqlDatabase& db) {
    QSqlQuery query(db);
    bool success = true;
    
    // Инициализация статистики, если таблица пуста
    success &= query.exec("INSERT OR IGNORE INTO statistics (count_registrations, count_visits, count_generations) VALUES (0, 0, 0)");
    
    // Создание администратора по умолчанию
    success &= query.exec("INSERT OR IGNORE INTO users(name, email, pass, is_admin) VALUES ('NewDev','admin@new-devs.ru','admin',true)");
    
    return success;
}