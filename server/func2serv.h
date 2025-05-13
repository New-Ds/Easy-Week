#ifndef FUNC2SERV_H
#define FUNC2SERV_H

#include <QByteArray>

/**
 * Парсинг входных данных.
 * @param input Входная строка.
 * @param socdes Дескриптор сокета.
 * @return Обработанная строка данных.
 */
QByteArray parsing(QString input, int socdes);

/**
 * Авторизация пользователя.
 * @param Входной список данных.
 * @return Результат авторизации в виде QByteArray.
 */
QByteArray auth(QStringList );

/**
 * Регистрация пользователя.
 * @param Входной список данных.
 * @return Результат регистрации в виде QByteArray.
 */
QByteArray reg(QStringList);

/**
 * Добавление продукта.
 * @param Входной список данных.
 * @return Результат добавления продукта в виде QByteArray.
 */
QByteArray add_product(QStringList);

/**
 * Получение статистики.
 * @return Статистика в виде QByteArray.
 */
QByteArray get_stat(/*QStringList*/);

/**
 * Проверка задания.
 * @return Результат проверки задания в виде QByteArray.
 */
QByteArray check_task(/*QStringList*/);

/**
 * Экспорт меню.
 * @return Результат экспорта меню в виде QByteArray.
 */
QByteArray menu_export(/*QStringList*/);

/**
 * Получение списка продуктов.
 * @param UserId Идентификатор пользователя.
 * @return Список продуктов в виде QByteArray.
 */
QByteArray get_products(QString UserId);

/**
 * Получение всех пользователей.
 * @return Список всех пользователей в виде QByteArray.
 */
QByteArray get_all_users();

/**
 * Получение стабильной статистики.
 * @return Стабильная статистика в виде QByteArray.
 */
QByteArray get_stable_stat();

/**
 * Получение количества пользователей.
 * @return Количество пользователей.
 */
int get_user_count();

/**
 * Получение количества продуктов.
 * @return Количество продуктов.
 */
int get_product_count();

/**
 * Получение динамической статистики.
 * @return Динамическая статистика в виде QByteArray.
 */
QByteArray get_dynamic_stat();

/**
 * Получение количества входов за неделю.
 * @return Количество входов за неделю.
 */
int get_weekly_logins();

/**
 * Получение количества входов за месяц.
 * @return Количество входов за месяц.
 */
int get_monthly_logins();

/**
 * Добавление рациона в избранное.
 * @param container Список данных.
 * @return Результат добавления в избранное в виде QByteArray.
 */
QByteArray add_favorite_ration(const QStringList& container);

/**
 * Добавление рациона в избранное для пользователя.
 * @param userId Идентификатор пользователя.
 * @param rationId Идентификатор рациона.
 * @return Результат добавления в избранное.
 */
bool add_ration_to_favorites(const QString& userId, const QString& rationId);

#include <QDebug>

#endif // FUNC2SERV_H
