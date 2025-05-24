#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <QObject>
#include <QByteArray>
#include <QStringList>

/**
 * @brief Сервис для управления аутентификацией пользователей
 */
class AuthService : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор сервиса аутентификации
     * @param parent Родительский объект
     */
    explicit AuthService(QObject *parent = nullptr);
    
    /**
     * @brief Аутентификация пользователя
     * @param params Параметры запроса
     * @return Результат аутентификации
     */
    QByteArray authenticateUser(const QStringList& params);
    
    /**
     * @brief Регистрация нового пользователя
     * @param params Параметры запроса
     * @return Результат регистрации
     */
    QByteArray registerUser(const QStringList& params);
    
    /**
     * @brief Получение списка всех пользователей
     * @return JSON с данными пользователей
     */
    QByteArray getAllUsers();
};

#endif // AUTHSERVICE_H