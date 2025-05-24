#ifndef AUTHREGWINDOW_H
#define AUTHREGWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class AuthRegWindow;
}
QT_END_NAMESPACE

/**
 * @brief Окно авторизации и регистрации
 */
class AuthRegWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор окна авторизации
     * @param parent Родительский виджет
     */
    AuthRegWindow(QWidget *parent = nullptr);
    
    /**
     * @brief Деструктор окна авторизации
     */
    ~AuthRegWindow();

private slots:
    /**
     * @brief Обработка нажатия кнопки переключения между авторизацией и регистрацией
     */
    void on_toRegButton_clicked();

    /**
     * @brief Обработка нажатия кнопки регистрации
     */
    void on_regButton_clicked();

    /**
     * @brief Обработка нажатия кнопки входа
     */
    void on_loginButton_clicked();

signals:
    /**
     * @brief Сигнал успешной авторизации
     * @param id ID пользователя
     * @param login Логин пользователя
     * @param email Email пользователя
     */
    void auth_ok(QString id, QString login, QString email);

private:
    Ui::AuthRegWindow *ui;
    
    /**
     * @brief Изменение типа отображения окна (авторизация/регистрация)
     * @param isReg Режим регистрации
     */
    void changeTypeToReg(bool isReg);
    
    /**
     * @brief Очистка полей ввода
     */
    void clear();
};
#endif // AUTHREGWINDOW_H