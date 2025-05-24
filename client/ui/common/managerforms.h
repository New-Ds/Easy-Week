#ifndef MANAGERFORMS_H
#define MANAGERFORMS_H

#include <QMainWindow>
#include "../product/add_product.h"
#include "../auth/authregwindow.h"
#include "../main/mainwindow.h"
#include "../../network/singleton.h"

namespace Ui {
    class ManagerForms;
}

/**
 * @brief Менеджер форм приложения
 * 
 * Управляет переключением между различными окнами приложения
 */
class ManagerForms : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор менеджера форм
     * @param parent Родительский виджет
     */
    explicit ManagerForms(QWidget *parent = nullptr);
    
    /**
     * @brief Деструктор менеджера форм
     */
    ~ManagerForms();

private:
    AuthRegWindow* curr_auth;         ///< Окно авторизации/регистрации
    MainWindow* main;                 ///< Главное окно приложения
    AddProductWindow* addProductWindow; ///< Окно добавления продукта
};

#endif // MANAGERFORMS_H