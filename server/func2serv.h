#ifndef FUNC2SERV_H
#define FUNC2SERV_H

#include <QByteArray>

QByteArray parsing(QString input, int socdes);

QByteArray auth(QStringList );
QByteArray reg(/*QStringList*/);
QByteArray get_stat(/*QStringList*/);
QByteArray check_task(/*QStringList*/);
QByteArray menu_export(/*QStringList*/);
QByteArray get_products(QStringList params);
QByteArray get_all_users();
QByteArray get_stable_stat();
int get_user_count();
int get_product_count();
QByteArray get_dynamic_stat();
int get_weekly_logins();
int get_monthly_logins();
QByteArray add_favorite_ration(const QStringList& container);
bool add_ration_to_favorites(const QString& userId, const QString& rationId);
#include <QDebug>

#endif // FUNC2SERV_H
