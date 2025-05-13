#ifndef FUNCTIONS_FOR_CLIENT_H
#define FUNCTIONS_FOR_CLIENT_H

#include <QString>
#include "Singleton.h"

/**
 * @brief Авторизация пользователя.
 * @param login Логин пользователя.
 * @param password Пароль пользователя.
 * @return Ответ от сервера.
 */
QString auth(QString login, QString password);

/**
 * @brief Регистрация нового пользователя.
 * @param login Логин пользователя.
 * @param password Пароль.
 * @param email Электронная почта.
 * @return true, если регистрация успешна; иначе — false.
 */
bool reg(QString login, QString password, QString email);

/**
 * @brief Получение стабильной статистики.
 * @return JSON-строка с данными статистики.
 */
QString get_stable_stat();

/**
 * @brief Получение динамической статистики.
 * @return JSON-строка с данными статистики.
 */
QString get_dynamic_stat();

/**
 * @brief Получение списка всех пользователей.
 * @return Массив байтов с данными пользователей.
 */
QByteArray get_all_users();

/**
 * @brief Проверка задачи (рациона).
 * @return Массив байтов с результатом проверки.
 */
QByteArray check_task();

/**
 * @brief Экспорт меню.
 * @return Массив байтов с экспортированными данными.
 */
QByteArray menu_export();

/**
 * @brief Получение всех продуктов пользователя.
 * @param userId Идентификатор пользователя.
 * @return Массив байтов с продуктами.
 */
QByteArray get_products(QString userId);

/**
 * @brief Добавление нового продукта.
 * @param id Идентификатор пользователя.
 * @param name Название продукта.
 * @param proteins Количество белков.
 * @param fats Количество жиров.
 * @param carbs Количество углеводов.
 * @param weight Вес продукта.
 * @param cost Стоимость продукта.
 * @param type Тип продукта.
 * @return Массив байтов с результатом операции.
 */
QByteArray add_product(QString id, QString name, int proteins, int fats, int carbs, int weight, int cost, int type);

/**
 * @brief Получение общего количества пользователей.
 * @return Количество пользователей.
 */
int get_user_count();

/**
 * @brief Получение общего количества продуктов.
 * @return Количество продуктов.
 */
int get_product_count();

/**
 * @brief Получение количества входов за неделю.
 * @return Количество входов.
 */
int get_weekly_logins();

/**
 * @brief Получение количества входов за месяц.
 * @return Количество входов.
 */
int get_monthly_logins();

/**
 * @brief Добавление рациона в избранное.
 * @param container Контейнер с параметрами рациона.
 * @return Массив байтов с результатом добавления.
 */
QByteArray add_favorite_ration(const QStringList& container);

/**
 * @brief Добавление существующего рациона в избранное.
 * @param userId Идентификатор пользователя.
 * @param rationId Идентификатор рациона.
 * @return true, если успешно; иначе — false.
 */
bool add_ration_to_favorites(const QString& userId, const QString& rationId);

#endif // FUNCTIONS_FOR_CLIENT_H
