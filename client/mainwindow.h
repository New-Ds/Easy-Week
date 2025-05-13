#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "functions_for_client.h"
#include "productCard.h"
#include "menuCard.h"
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

/**
 * @brief Главное окно клиента.
 * 
 * Отвечает за отображение основной информации, взаимодействие с продуктами,
 * пользователями, рационом и статистикой.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса MainWindow.
     * @param parent Родительский виджет.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор.
     */
    ~MainWindow();

    QString id;       ///< Идентификатор текущего пользователя.
    QString login;    ///< Логин пользователя.
    QString password; ///< Пароль пользователя.
    QString email;    ///< Электронная почта пользователя.

public slots:
    /**
     * @brief Показывает главное окно.
     */
    void slot_show();

    /**
     * @brief Устанавливает данные текущего пользователя.
     * @param id Идентификатор пользователя.
     * @param login Логин.
     * @param email Электронная почта.
     */
    void set_current_user(QString id, QString login, QString email);

    /**
     * @brief Обрабатывает добавление нового продукта.
     * @param name Название продукта.
     * @param proteins Белки.
     * @param fats Жиры.
     * @param carbs Углеводы.
     * @param weight Вес.
     * @param cost Стоимость.
     * @param type Тип продукта.
     */
    void handleProductAdded(QString name, int proteins, int fats, int carbs, int weight, int cost, int type);

private:
    Ui::MainWindow *ui; ///< Указатель на UI-элементы окна.

private slots:
    /**
     * @brief Обработчик нажатия на кнопку "Стабильная статистика".
     */
    void on_stableStatButton_clicked();

    /**
     * @brief Обработчик нажатия на кнопку "Динамическая статистика".
     */
    void on_dynamicStatButton_clicked();

    /**
     * @brief Обработчик нажатия на кнопку "Список пользователей".
     */
    void on_tableUsersButton_clicked();

    /**
     * @brief Обработчик нажатия на кнопку "Список продуктов".
     */
    void on_productListButton_clicked();

    /**
     * @brief Обработчик нажатия на кнопку "Создать рацион".
     */
    void on_createMenButton_clicked();

    /**
     * @brief Обработчик нажатия на кнопку "Добавить продукт".
     */
    void on_addProductButton_clicked();

    /**
     * @brief Обработчик нажатия на кнопку "Выход".
     */
    void on_exitButton_clicked();

signals:
    /**
     * @brief Сигнал, указывающий на необходимость открыть окно добавления продукта.
     */
    void add_product();
};

#endif // MAINWINDOW_H
