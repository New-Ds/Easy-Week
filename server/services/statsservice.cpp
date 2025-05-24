#include "statsservice.h"
#include "../database/databasesingleton.h"

StatsService::StatsService(QObject *parent) : QObject(parent)
{
}

QByteArray StatsService::getStatistics()
{
    return "Your Statistic: null\r\n";
}

QByteArray StatsService::getStableStats()
{
    int userCount = 0;
    int productCount = 0;

    userCount = getUserCount();
    productCount = getProductCount();

    // Формируем строку ответа
    QString response = "Users: " + QString::number(userCount) + "\r\n" +
                       "Products: " + QString::number(productCount) + "\r\n";

    return response.toUtf8();
}

QByteArray StatsService::getDynamicStats()
{
    int weeklyLogins = 0;
    int monthlyLogins = 0;

    // Получаем данные из БД (пока заглушки)
    weeklyLogins = getWeeklyLogins();
    monthlyLogins = getMonthlyLogins();

    // Формируем строку ответа
    QString response = "Logins per week: " + QString::number(weeklyLogins) + "\r\n" +
                       "Logins per month: " + QString::number(monthlyLogins) + "\r\n";

    return response.toUtf8();
}

int StatsService::getUserCount()
{
    // Здесь будет SQL-запрос, пока заглушка
    return 152; // Примерное значение
}

int StatsService::getProductCount()
{
    // Здесь будет SQL-запрос, пока заглушка
    return 732; // Примерное значение
}

int StatsService::getWeeklyLogins()
{
    // Заглушка, пока без БД
    return 78; // Примерное значение
}

int StatsService::getMonthlyLogins()
{
    // Заглушка, пока без БД
    return 312; // Примерное значение
}