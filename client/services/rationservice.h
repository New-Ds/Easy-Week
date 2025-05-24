#ifndef CLIENT_RATIONSERVICE_H
#define CLIENT_RATIONSERVICE_H

#include <QString>
#include <QByteArray>
#include <QStringList>

/**
 * @brief Сервис для работы с рационами на стороне клиента
 */
class RationService
{
public:
    /**
     * @brief Добавление избранного рациона
     * @param container Параметры запроса
     * @return Ответ сервера
     */
    static QByteArray addFavoriteRation(const QStringList& container);
    
    /**
     * @brief Добавление рациона в избранное
     * @param userId ID пользователя
     * @param rationId ID рациона
     * @return Успешность операции
     */
    static bool addRationToFavorites(const QString& userId, const QString& rationId);
};

#endif // CLIENT_RATIONSERVICE_H