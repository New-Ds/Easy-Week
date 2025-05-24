#ifndef CLIENT_PRODUCTSERVICE_H
#define CLIENT_PRODUCTSERVICE_H

#include <QString>
#include <QByteArray>

/**
 * @brief Сервис для работы с продуктами на стороне клиента
 */
class ProductService
{
public:
    /**
     * @brief Получение продуктов пользователя
     * @param userId ID пользователя
     * @return JSON с данными продуктов
     */
    static QByteArray getProductsByUser(const QString& userId);
    
    /**
     * @brief Добавление нового продукта
     * @param id ID пользователя
     * @param name Название продукта
     * @param proteins Содержание белков
     * @param fats Содержание жиров
     * @param carbs Содержание углеводов
     * @param weight Вес порции
     * @param cost Стоимость
     * @param type Тип продукта
     * @return Ответ сервера
     */
    static QByteArray addProduct(const QString& id, const QString& name, int proteins, int fats, int carbs, int weight, int cost, int type);
};

#endif // CLIENT_PRODUCTSERVICE_H