#ifndef CLIENT_AUTHSERVICE_H
#define CLIENT_AUTHSERVICE_H

#include <QString>
#include <QByteArray>

/**
 * @brief Сервис для аутентификации на стороне клиента
 */
class AuthService
{
public:
    /**
     * @brief Аутентификация пользователя
     * @param email Email пользователя
     * @param password Пароль пользователя
     * @return Ответ сервера
     */
    static QString authenticate(const QString& email, const QString& password);
    
    /**
     * @brief Регистрация нового пользователя
     * @param login Логин пользователя
     * @param password Пароль пользователя
     * @param email Email пользователя
     * @return Успешность регистрации
     */
    static bool registerUser(const QString& login, const QString& password, const QString& email);
    
    /**
     * @brief Получение списка всех пользователей (только для администраторов)
     * @return JSON с данными пользователей
     */
    static QByteArray getAllUsers();
};

#endif // CLIENT_AUTHSERVICE_H