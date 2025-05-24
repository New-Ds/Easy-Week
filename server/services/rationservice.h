#ifndef RATIONSERVICE_H
#define RATIONSERVICE_H

#include <QObject>
#include <QByteArray>
#include <QStringList>

/**
 * @brief Сервис для управления рационами
 */
class RationService : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор сервиса рационов
     * @param parent Родительский объект
     */
    explicit RationService(QObject *parent = nullptr);
    
    /**
     * @brief Добавление избранного рациона
     * @param params Параметры запроса
     * @return Результат добавления
     */
    QByteArray addFavoriteRation(const QStringList& params);
    
private:
    /**
     * @brief Добавление рациона в избранное
     * @param userId ID пользователя
     * @param rationId ID рациона
     * @return Успешность операции
     */
    bool addRationToFavorites(const QString& userId, const QString& rationId);
};

#endif // RATIONSERVICE_H