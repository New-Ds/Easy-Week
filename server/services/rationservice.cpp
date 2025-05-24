#include "rationservice.h"
#include <QDebug>

RationService::RationService(QObject *parent) : QObject(parent)
{
}

QByteArray RationService::addFavoriteRation(const QStringList& params)
{
    if (params.size() < 3) {
        return "Error: invalid parameters for add_favorite_ration\r\n";
    }
    
    QString userId = params[1]; // ID пользователя
    QString rationId = params[2]; // ID рациона

    bool success = addRationToFavorites(userId, rationId);

    if (success) {
        return "Ration successfully added to favorites\r\n";
    } else {
        return "Error: failed to add ration to favorites\r\n";
    }
}

bool RationService::addRationToFavorites(const QString& userId, const QString& rationId)
{
    qDebug() << "Adding ration for user:" << userId << ", ration ID:" << rationId;
    return true; // Заглушка, потом заменить на SQL-запрос
}