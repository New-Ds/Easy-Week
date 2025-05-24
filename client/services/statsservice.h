#ifndef CLIENT_STATSSERVICE_H
#define CLIENT_STATSSERVICE_H

#include <QString>

/**
 * @brief Сервис для работы со статистикой на стороне клиента
 */
class StatsService
{
public:
    /**
     * @brief Получение стабильной статистики
     * @return Данные статистики
     */
    static QString getStableStats();
    
    /**
     * @brief Получение динамической статистики
     * @return Данные статистики
     */
    static QString getDynamicStats();
    
    /**
     * @brief Получение количества пользователей
     * @return Количество пользователей
     */
    static int getUserCount();
    
    /**
     * @brief Получение количества продуктов
     * @return Количество продуктов
     */
    static int getProductCount();
    
    /**
     * @brief Получение количества входов за неделю
     * @return Количество входов за неделю
     */
    static int getWeeklyLogins();
    
    /**
     * @brief Получение количества входов за месяц
     * @return Количество входов за месяц
     */
    static int getMonthlyLogins();
};

#endif // CLIENT_STATSSERVICE_H