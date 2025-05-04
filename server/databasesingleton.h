#ifndef DATABASESINGLETON_H
#define DATABASESINGLETON_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariantMap>
#include <QVector>

class DataBaseSingleton;

// Класс-разрушитель для корректного удаления Singleton
class SingletonDestroyer {
private:
    DataBaseSingleton* p_instance; // Указатель на экземпляр Singleton
public:
    ~SingletonDestroyer(); // Деструктор для удаления Singleton
    void initialize(DataBaseSingleton* p); // Инициализация указателя
};

// Основной класс для работы с базой данных
class DataBaseSingleton {
private:
    static DataBaseSingleton* p_instance;   // Единственный экземпляр класса
    static SingletonDestroyer destroyer;    // Объект-разрушитель
    QSqlDatabase db;                        // Объект базы данных

    DataBaseSingleton();                    // Приватный конструктор
    DataBaseSingleton(const DataBaseSingleton&) = delete; // Запрет копирования
    DataBaseSingleton& operator=(const DataBaseSingleton&) = delete;
    ~DataBaseSingleton() = default;         // Приватный деструктор
    friend class SingletonDestroyer;        // Дружественный класс для доступа к деструктору

public:
    // Получение экземпляра Singleton
    static DataBaseSingleton* getInstance();

    // Инициализация БД: имя файла, создание таблиц
    bool initialize(const QString& databaseName);

    // Выполнение параметризованного SQL-запроса
    QSqlQuery executeQuery(const QString& query, const QVariantMap& params = QVariantMap());

    // Методы для работы с таблицей users
    bool checkUserCredentials(const QString& login, const QString& password);
    bool addUser(const QString& name, const QString& email, const QString& password, bool isAdmin = false);

    // Методы для работы с таблицей products
    bool addProduct(int userId, const QString& name, int proteins, int fatness, int carbs, int weight, int cost, int type);
    QVector<QVariantMap> getProductsByUser(int userId);

    // Методы для работы с таблицей favorites
    bool addFavoriteRation(int userId, const QVector<int>& productIds, int calories, int allCost, int allWeight);
    QVector<QVariantMap> getFavoritesByUser(int userId);

    // Методы для работы с таблицей statistics
    bool updateStatistics(int registrations, int visits, int generations);
    QVariantMap getStatistics();
};

#endif // DATABASESINGLETON_H
