#ifndef FUNCTIONS_FOR_CLIENT_H
#define FUNCTIONS_FOR_CLIENT_H

#include <QString>
#include "Singleton.h"


QString auth(QString login, QString password);
bool reg(QString login, QString password, QString email);
QString get_stable_stat(/* какие-то аргументы, если потребуются */);
QString get_dynamic_stat(/* какие-то аргументы, если потребуются */);
QByteArray get_all_users();

QByteArray check_task(/*QStringList*/);
QByteArray menu_export(/*QStringList*/);
QByteArray get_products(QString userId);

QByteArray add_product(QString id, QString name, int proteins, int fats, int carbs, int weight, int cost, int type);

int get_user_count();
int get_product_count();
int get_weekly_logins();
int get_monthly_logins();
QByteArray add_favorite_ration(const QStringList& container);
bool add_ration_to_favorites(const QString& userId, const QString& rationId);



#endif // FUNCTIONS_FOR_CLIENT_H
