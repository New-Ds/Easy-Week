#include "productservice.h"
#include "../database/databasesingleton.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

ProductService::ProductService(QObject *parent) : QObject(parent)
{
}

QByteArray ProductService::addProduct(const QStringList& params)
{
    if (params.size() != 9) {
        return "add_product//failed//Неверные аргументы\r\n";
    }

    DataBaseSingleton* db = DataBaseSingleton::getInstance();
    int userId = params[1].toInt();
    QString name = params[2];

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

QByteArray ProductService::getProductsByUser(const QString& userId)
{
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