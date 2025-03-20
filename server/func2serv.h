#ifndef FUNC2SERV_H
#define FUNC2SERV_H

#include <QByteArray>

QByteArray parsing(QString input, int socdes);
/**
    \brief Шаблонная функция суммирования двух объектов

    \tparam T - любой тип, для которого определен оператор суммирования 
    и оператор присваивания

    \param [in] a Первый объект, который нужно сложить
    \param [in] b Второй объект, который нужно сложить

    \return Новый объект типа *T*, равный сумме *a* и *b*.
*/
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
