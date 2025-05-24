#include "productservice.h"
#include "../network/singleton.h"
#include <QDebug>

QByteArray ProductService::getProductsByUser(const QString& userId)
{
    NetworkSingleton& client = NetworkSingleton::getInstance();
    QStringList params = {"user", userId, "get_products"};
    QByteArray response = client.sendMessage(params);
    return response;
}

QByteArray ProductService::addProduct(const QString& id, const QString& name, int proteins, int fats, int carbs, int weight, int cost, int type)
{
    NetworkSingleton& client = NetworkSingleton::getInstance();
    QStringList params = {
        "add_product",
        id,
        name,
        QString::number(proteins),
        QString::number(fats),
        QString::number(carbs),
        QString::number(weight),
        QString::number(cost),
        QString::number(type)
    };
    QByteArray response = client.sendMessage(params);
    return response;
}