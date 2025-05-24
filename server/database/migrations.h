#ifndef MIGRATIONS_H
#define MIGRATIONS_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

/**
 * @brief Класс для управления миграциями базы данных
 */
class Migrations {
public:
    /**
     * @brief Выполняет все миграции базы данных
     * @param db Ссылка на открытое соединение с БД
     * @return true в случае успеха, false при ошибке
     */
    static bool runMigrations(QSqlDatabase& db);

private:
    /**
     * @brief Создает основные таблицы базы данных
     * @param db Ссылка на открытое соединение с БД
     * @return true в случае успеха, false при ошибке
     */
    static bool createTables(QSqlDatabase& db);
    
    /**
     * @brief Инициализирует начальные данные
     * @param db Ссылка на открытое соединение с БД
     * @return true в случае успеха, false при ошибке
     */
    static bool seedInitialData(QSqlDatabase& db);
};

#endif // MIGRATIONS_H