#include "statsservice.h"
#include "../network/singleton.h"
#include <QDebug>

QString StatsService::getStableStats()
{
    NetworkSingleton& client = NetworkSingleton::getInstance();
    QString stat = client.sendMessage(QStringList{"admin", "stable_stat"});
    return stat;
}

QString StatsService::getDynamicStats()
{
    NetworkSingleton& client = NetworkSingleton::getInstance();
    QString stat = client.sendMessage(QStringList{"admin", "dynamic_stat"});
    return stat;
}

int StatsService::getUserCount()
{
    // Парсинг данных из getStableStats()
    // Здесь должна быть реализация разбора ответа
    return 152; // Примерное значение (заглушка)
}

int StatsService::getProductCount()
{
    // Парсинг данных из getStableStats()
    // Здесь должна быть реализация разбора ответа
    return 732; // Примерное значение (заглушка)
}

int StatsService::getWeeklyLogins()
{
    // Парсинг данных из getDynamicStats()
    // Здесь должна быть реализация разбора ответа
    return 78; // Примерное значение (заглушка)
}

int StatsService::getMonthlyLogins()
{
    // Парсинг данных из getDynamicStats()
    // Здесь должна быть реализация разбора ответа
    return 312; // Примерное значение (заглушка)
}