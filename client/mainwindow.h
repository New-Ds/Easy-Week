#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "functions_for_client.h"
#include "productCard.h"
#include "menuCard.h"
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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString id;
    QString login;
    QString password;
    QString email;


    menuCard* generateMenuCardForDay(const QString& dayName, const QJsonArray& productArray, QWidget* parent, int index);

public slots:
    void slot_show();
    void set_current_user(QString id, QString login, QString email);
    void handleProductAdded( QString name, int proteins, int fats, int carbs, int weight, int cost, int type);
    void updateMenuCard(int cardIndex);

private:
    Ui::MainWindow *ui;
    // Добавить эти поля после существующих
    QWidget* usersTableContainer = nullptr;
    QTableWidget* usersTable = nullptr;
    QComboBox* usersFilterCombo = nullptr;
    QLineEdit* usersSearchLine = nullptr;
    QJsonArray allUsersData;

    // Вспомогательные методы для таблицы пользователей
    void createUsersTableUI();
    void populateUsersTable(const QByteArray& jsonData);
    void filterUsersTable();
    void styleUsersTable();

private slots:
    void on_stableStatButton_clicked();
    void on_dynamicStatButton_clicked();
    void on_tableUsersButton_clicked();
    void on_productListButton_clicked();
    void on_createMenButton_clicked();
    void on_addProductButton_clicked();
    void on_exitButton_clicked();

    // Добавить только этот слот после существующих
    void refreshUsersTable();

signals:
    void add_product();
};

#endif // MAINWINDOW_H
