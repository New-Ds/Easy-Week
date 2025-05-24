#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../services/authservice.h"
#include "../../services/productservice.h"
#include "../../services/statsservice.h"
#include "../product/productcard.h"
#include "../menu/menucard.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHeaderView>

namespace Ui {
class MainWindow;
}

/**
 * @brief Главное окно приложения
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор главного окна
     * @param parent Родительский виджет
     */
    explicit MainWindow(QWidget *parent = nullptr);
    
    /**
     * @brief Деструктор главного окна
     */
    ~MainWindow();

    QString id;       ///< ID текущего пользователя
    QString login;    ///< Логин текущего пользователя
    QString email;    ///< Email текущего пользователя

    /**
     * @brief Генерация карточки меню для дня недели
     * @param dayName Название дня недели
     * @param productArray Массив продуктов
     * @param parent Родительский виджет
     * @param index Индекс карточки
     * @return Указатель на созданную карточку
     */
    MenuCard* generateMenuCardForDay(const QString& dayName, const QJsonArray& productArray, QWidget* parent, int index);

public slots:
    /**
     * @brief Отображение окна
     */
    void slot_show();
    
    /**
     * @brief Установка текущего пользователя
     * @param id ID пользователя
     * @param login Логин пользователя
     * @param email Email пользователя
     */
    void set_current_user(QString id, QString login, QString email);
    
    /**
     * @brief Обработка добавления продукта
     * @param name Название продукта
     * @param proteins Содержание белков
     * @param fats Содержание жиров
     * @param carbs Содержание углеводов
     * @param weight Вес порции
     * @param cost Стоимость
     * @param type Тип продукта
     */
    void handleProductAdded(QString name, int proteins, int fats, int carbs, int weight, int cost, int type);
    
    /**
     * @brief Обновление карточки меню
     * @param cardIndex Индекс карточки
     */
    void updateMenuCard(int cardIndex);

private:
    Ui::MainWindow *ui;
    QWidget* usersTableContainer = nullptr;   ///< Контейнер для таблицы пользователей
    QTableWidget* usersTable = nullptr;       ///< Таблица пользователей
    QComboBox* usersFilterCombo = nullptr;    ///< Комбобокс для фильтрации
    QLineEdit* usersSearchLine = nullptr;     ///< Поле для поиска
    QJsonArray allUsersData;                  ///< Данные всех пользователей

    /**
     * @brief Создание UI таблицы пользователей
     */
    void createUsersTableUI();
    
    /**
     * @brief Заполнение таблицы пользователей
     * @param jsonData JSON с данными пользователей
     */
    void populateUsersTable(const QByteArray& jsonData);
    
    /**
     * @brief Фильтрация таблицы пользователей
     */
    void filterUsersTable();
    
    /**
     * @brief Стилизация таблицы пользователей
     */
    void styleUsersTable();

private slots:
    /**
     * @brief Обработка нажатия кнопки стабильной статистики
     */
    void on_stableStatButton_clicked();
    
    /**
     * @brief Обработка нажатия кнопки динамической статистики
     */
    void on_dynamicStatButton_clicked();
    
    /**
     * @brief Обработка нажатия кнопки таблицы пользователей
     */
    void on_tableUsersButton_clicked();
    
    /**
     * @brief Обработка нажатия кнопки списка продуктов
     */
    void on_productListButton_clicked();
    
    /**
     * @brief Обработка нажатия кнопки создания меню
     */
    void on_createMenButton_clicked();
    
    /**
     * @brief Обработка нажатия кнопки добавления продукта
     */
    void on_addProductButton_clicked();
    
    /**
     * @brief Обработка нажатия кнопки выхода
     */
    void on_exitButton_clicked();

    /**
     * @brief Обновление таблицы пользователей
     */
    void refreshUsersTable();

    /**
     * @brief Обработка нажатия кнопки экспорта
     */
    void on_exportButton_clicked();

signals:
    /**
     * @brief Сигнал о необходимости добавления продукта
     */
    void add_product();
};

#endif // MAINWINDOW_H
