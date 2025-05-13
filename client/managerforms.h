#ifndef MANAGERFORMS_H
#define MANAGERFORMS_H

#include <QMainWindow>
#include "add_product.h"
#include "authregwindow.h"
#include "mainwindow.h"
#include "Singleton.h"

namespace Ui {
    class ManagerForms;
}

/**
 * @brief Класс для управления окнами приложения.
 * 
 * Отвечает за создание и переключение между окнами авторизации, 
 * главного интерфейса и окна добавления продукта.
 */
class ManagerForms : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса ManagerForms.
     * @param parent Родительский виджет.
     */
    explicit ManagerForms(QWidget *parent = nullptr);

    /**
     * @brief Деструктор.
     */
    ~ManagerForms();

private:
    AuthRegWindow *curr_auth;           ///< Указатель на окно авторизации и регистрации.
    MainWindow *main;                   ///< Указатель на главное окно приложения.
    AddProductWindow *addProductWindow; ///< Указатель на окно добавления продукта.
};

#endif // MANAGERFORMS_H
