#ifndef PRODUCTSERVICE_H
#define PRODUCTSERVICE_H

#include <QObject>
#include <QByteArray>
#include <QStringList>

/**
 * @brief Сервис для управления продуктами
 */
class ProductService : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор сервиса продуктов
     * @param parent Родительский объект
     */
    explicit ProductService(QObject *parent = nullptr);
    
    /**
     * @brief Добавление нового продукта
     * @param params Параметры запроса
     * @return Результат добавления
     */
    QByteArray addProduct(const QStringList& params);
    
    /**
     * @brief Получение продуктов пользователя
     * @param userId ID пользователя
     * @return JSON с данными продуктов
     */
    QByteArray getProductsByUser(const QString& userId);
};

#endif // PRODUCTSERVICE_H