#ifndef DATABASESINGLETON_H
#define DATABASESINGLETON_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariantMap>
#include <QVector>

class DataBaseSingleton;

/**
 * @brief Класс-разрушитель для корректного удаления Singleton
 */
class SingletonDestroyer {
private:
    DataBaseSingleton* p_instance; ///< Указатель на экземпляр Singleton
public:
    ~SingletonDestroyer(); ///< Деструктор для удаления Singleton
    void initialize(DataBaseSingleton* p); ///< Инициализация указателя
};

/**
 * @brief Основной класс для работы с базой данных
 * 
 * Реализует паттерн Singleton для централизованного доступа к БД
 */
class DataBaseSingleton {
private:
    static DataBaseSingleton* p_instance;   ///< Единственный экземпляр класса
    static SingletonDestroyer destroyer;    ///< Объект-разрушитель
    QSqlDatabase db;                        ///< Объект базы данных

    DataBaseSingleton();                    ///< Приватный конструктор
    DataBaseSingleton(const DataBaseSingleton&) = delete; ///< Запрет копирования
    DataBaseSingleton& operator=(const DataBaseSingleton&) = delete;
    ~DataBaseSingleton() = default;         ///< Приватный деструктор
    friend class SingletonDestroyer;        ///< Дружественный класс для доступа к деструктору

public:
    /**
     * @brief Получение экземпляра Singleton
     * @return Указатель на экземпляр DataBaseSingleton
     */
    static DataBaseSingleton* getInstance();

    /**
     * @brief Инициализация БД
     * @param databaseName Имя файла базы данных
     * @return true в случае успеха, false при ошибке
     */
    bool initialize(const QString& databaseName);

    /**
     * @brief Выполнение параметризованного SQL-запроса
     * @param query SQL-запрос
     * @param params Параметры запроса
     * @return Объект QSqlQuery с результатом запроса
     */
    QSqlQuery executeQuery(const QString& query, const QVariantMap& params = QVariantMap());

    // Методы для работы с таблицей users
    /**
     * @brief Проверка учетных данных пользователя
     * @param email Email пользователя
     * @param password Пароль пользователя
     * @return true если данные верны, false в противном случае
     */
    bool checkUserCredentials(const QString& email, const QString& password);
    
    /**
     * @brief Добавление нового пользователя
     * @param name Имя пользователя
     * @param email Email пользователя
     * @param password Пароль пользователя
     * @param isAdmin Флаг администратора
     * @return true в случае успеха, false при ошибке
     */
    bool addUser(const QString& name, const QString& email, const QString& password, bool isAdmin = false);

    // Методы для работы с таблицей products
    /**
     * @brief Добавление нового продукта
     * @param userId ID пользователя
     * @param name Название продукта
     * @param proteins Содержание белков
     * @param fatness Содержание жиров
     * @param carbs Содержание углеводов
     * @param weight Вес порции
     * @param cost Стоимость
     * @param type Тип продукта
     * @return true в случае успеха, false при ошибке
     */
    bool addProduct(int userId, const QString& name, int proteins, int fatness, int carbs, int weight, int cost, int type);
    
    /**
     * @brief Получение списка продуктов пользователя
     * @param userId ID пользователя
     * @return Вектор с данными продуктов
     */
    QVector<QVariantMap> getProductsByUser(int userId);

    // Методы для работы с таблицей favorites
    /**
     * @brief Добавление избранного рациона
     * @param userId ID пользователя
     * @param productIds Список ID продуктов
     * @param calories Калорийность
     * @param allCost Общая стоимость
     * @param allWeight Общий вес
     * @return true в случае успеха, false при ошибке
     */
    bool addFavoriteRation(int userId, const QVector<int>& productIds, int calories, int allCost, int allWeight);
    
    /**
     * @brief Получение списка избранных рационов пользователя
     * @param userId ID пользователя
     * @return Вектор с данными рационов
     */
    QVector<QVariantMap> getFavoritesByUser(int userId);

    // Методы для работы с таблицей statistics
    /**
     * @brief Обновление статистики
     * @param registrations Количество регистраций
     * @param visits Количество посещений
     * @param generations Количество генераций
     * @return true в случае успеха, false при ошибке
     */
    bool updateStatistics(int registrations, int visits, int generations);
    
    /**
     * @brief Получение статистики
     * @return Объект с данными статистики
     */
    QVariantMap getStatistics();
};

#endif // DATABASESINGLETON_H