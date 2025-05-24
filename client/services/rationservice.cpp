#include "rationservice.h"
#include "../network/singleton.h"
#include <QDebug>

QByteArray RationService::addFavoriteRation(const QStringList& container)
{
    NetworkSingleton& client = NetworkSingleton::getInstance();
    QByteArray response = client.sendMessage(container);
    return response;
}

bool RationService::addRationToFavorites(const QString& userId, const QString& rationId)
{
    NetworkSingleton& client = NetworkSingleton::getInstance();
    QStringList params = {"user", userId, "add_favorite_ration", rationId};
    QByteArray response = client.sendMessage(params);
    
    // Простая проверка успешности операции
    return response.contains("successfully");
}