#ifndef STATSSERVICE_H
#define STATSSERVICE_H

#include <QObject>
#include <QByteArray>

/**
 * @brief Сервис для управления статистикой
 */
class StatsService : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор сервиса статистики
     * @param parent Родительский объект
     */
    explicit StatsService(QObject *parent = nullptr);
    
    /**
     * @brief Получение общей статистики
     * @return Данные статистики
     */
    QByteArray getStatistics();
    
    /**
     * @brief Получение стабильной статистики
     * @return Данные стабильной статистики
     */
    QByteArray getStableStats();
    
    /**
     * @brief Получение динамической статистики
     * @return Данные динамической статистики
     */
    QByteArray getDynamicStats();
    
private:
    /**
     * @brief Получение количества пользователей
     * @return Количество пользователей
     */
    int getUserCount();
    
    /**
     * @brief Получение количества продуктов
     * @return Количество продуктов
     */
    int getProductCount();
    
    /**
     * @brief Получение количества входов за неделю
     * @return Количество входов за неделю
     */
    int getWeeklyLogins();
    
    /**
     * @brief Получение количества входов за месяц
     * @return Количество входов за месяц
     */
    int getMonthlyLogins();
};

#endif // STATSSERVICE_H