#ifndef AUTHREGWINDOW_H
#define AUTHREGWINDOW_H

#include <QMainWindow>
#include "functions_for_client.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AuthRegWindow;
}
QT_END_NAMESPACE

/**
 * @brief Класс окна авторизации и регистрации.
 *
 * Этот класс реализует окно для входа в систему и создания нового аккаунта.
 * Содержит обработчики для переключения между формами, а также подтверждения входа/регистрации.
 */
class AuthRegWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор окна авторизации/регистрации.
     * @param parent Родительский виджет.
     */
    AuthRegWindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор.
     */
    ~AuthRegWindow();

private slots:
    /**
     * @brief Обработчик нажатия кнопки "Регистрация".
     * Переключает окно в режим регистрации.
     */
    void on_toRegButton_clicked();

    /**
     * @brief Обработчик подтверждения регистрации.
     * Отправляет данные нового пользователя на сервер.
     */
    void on_regButton_clicked();

    /**
     * @brief Обработчик подтверждения входа.
     * Отправляет данные пользователя на сервер для авторизации.
     */
    void on_loginButton_clicked();

signals:
    /**
     * @brief Сигнал об успешной авторизации.
     * @param id Идентификатор пользователя.
     * @param login Логин пользователя.
     * @param email Электронная почта пользователя.
     */
    void auth_ok(QString id, QString login, QString email);

private:
    Ui::AuthRegWindow *ui; /**< Указатель на интерфейс. */

    /**
     * @brief Вспомогательная функция переключения режима окна.
     * @param to_reg Если true — включается режим регистрации.
     */
    void change_type_to_reg(bool to_reg);

    /**
     * @brief Очистка всех полей ввода.
     */
    void clear();
};

#endif // AUTHREGWINDOW_H
