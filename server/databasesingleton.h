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
 * @brief Класс для разрушения экземпляра Singleton.
 * 
 * Используется для корректного удаления экземпляра DataBaseSingleton.
 */
class SingletonDestroyer {
private:
    DataBaseSingleton* p_instance; ///< Указатель на экземпляр Singleton
public:
    /**
     * @brief Деструктор для удаления Singleton.
     * 
     * Уничтожает экземпляр Singleton, если он существует.
     */
    ~SingletonDestroyer();

    /**
     * @brief Инициализация указателя на экземпляр Singleton.
     * 
     * @param p Указатель на экземпляр Singleton.
     */
    void initialize(DataBaseSingleton* p);
};

/**
 * @brief Класс для работы с базой данных.
 * 
 * Реализует паттерн Singleton для подключения к базе данных, выполнения SQL-запросов,
 * а также управления данными пользователей, продуктов, избранных рационов и статистики.
 */
class DataBaseSingleton {
private:
    static DataBaseSingleton* p_instance;   ///< Единственный экземпляр класса
    static SingletonDestroyer destroyer;    ///< Объект-разрушитель
    QSqlDatabase db;                        ///< Объект базы данных

    /**
     * @brief Приватный конструктор.
     * 
     * Запрещает создание экземпляров класса напрямую.
     */
    DataBaseSingleton();

    DataBaseSingleton(const DataBaseSingleton&) = delete; ///< Запрещает копирование экземпляра
    DataBaseSingleton& operator=(const DataBaseSingleton&) = delete; ///< Запрещает присваивание

    /**
     * @brief Приватный деструктор.
     * 
     * Закрыт для предотвращения удаления экземпляра Singleton извне.
     */
    ~DataBaseSingleton() = default;

    friend class SingletonDestroyer;        ///< Дружественный класс для доступа к деструктору

public:
    /**
     * @brief Получение единственного экземпляра Singleton.
     * 
     * @return Экземпляр класса DataBaseSingleton.
     */
    static DataBaseSingleton* getInstance();

    /**
     * @brief Инициализация базы данных.
     * 
     * Создает соединение с базой данных и выполняет необходимые операции для создания таблиц.
     * 
     * @param databaseName Имя файла базы данных.
     * @return true, если инициализация успешна, иначе false.
     */
    bool initialize(const QString& databaseName);

    /**
     * @brief Выполнение SQL-запроса с параметрами.
     * 
     * @param query SQL-запрос в виде строки.
     * @param params Параметры для SQL-запроса.
     * @return Результат выполнения запроса в виде QSqlQuery.
     */
    QSqlQuery executeQuery(const QString& query, const QVariantMap& params = QVariantMap());

    /**
     * @brief Проверка учетных данных пользователя.
     * 
     * @param login Логин пользователя.
     * @param password Пароль пользователя.
     * @return true, если учетные данные корректны, иначе false.
     */
    bool checkUserCredentials(const QString& login, const QString& password);

    /**
     * @brief Добавление нового пользователя в базу данных.
     * 
     * @param name Имя пользователя.
     * @param email Электронная почта пользователя.
     * @param password Пароль пользователя.
     * @param isAdmin Флаг администратора (по умолчанию false).
     * @return true, если пользователь добавлен, иначе false.
     */
    bool addUser(const QString& name, const QString& email, const QString& password, bool isAdmin = false);

    /**
     * @brief Добавление продукта в базу данных.
     * 
     * @param userId Идентификатор пользователя.
     * @param name Название продукта.
     * @param proteins Количество белков в продукте.
     * @param fatness Количество жиров в продукте.
     * @param carbs Количество углеводов в продукте.
     * @param weight Вес продукта.
     * @param cost Стоимость продукта.
     * @param type Тип продукта.
     * @return true, если продукт добавлен, иначе false.
     */
    bool addProduct(int userId, const QString& name, int proteins, int fatness, int carbs, int weight, int cost, int type);

    /**
     * @brief Получение продуктов для конкретного пользователя.
     * 
     * @param userId Идентификатор пользователя.
     * @return Список продуктов, принадлежащих пользователю.
     */
    QVector<QVariantMap> getProductsByUser(int userId);

    /**
     * @brief Добавление рациона в избранное.
     * 
     * @param userId Идентификатор пользователя.
     * @param productIds Список идентификаторов продуктов.
     * @param calories Общее количество калорий.
     * @param allCost Общая стоимость рациона.
     * @param allWeight Общий вес рациона.
     * @return true, если рацион добавлен, иначе false.
     */
    bool addFavoriteRation(int userId, const QVector<int>& productIds, int calories, int allCost, int allWeight);

    /**
     * @brief Получение избранных рационов пользователя.
     * 
     * @param userId Идентификатор пользователя.
     * @return Список избранных рационов пользователя.
     */
    QVector<QVariantMap> getFavoritesByUser(int userId);

    /**
     * @brief Обновление статистики.
     * 
     * @param registrations Количество регистраций.
     * @param visits Количество посещений.
     * @param generations Количество генераций.
     * @return true, если статистика обновлена, иначе false.
     */
    bool updateStatistics(int registrations, int visits, int generations);

    /**
     * @brief Получение статистики.
     * 
     * @return Словарь с данными статистики.
     */
    QVariantMap getStatistics();
};

#endif // DATABASESINGLETON_H
