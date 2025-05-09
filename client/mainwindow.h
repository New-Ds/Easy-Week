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

public slots:
    void slot_show();
    void set_current_user(QString id, QString login, QString email);
    void handleProductAdded( QString name, int proteins, int fats, int carbs, int weight, int cost, int type);

private:
    Ui::MainWindow *ui;

private slots:
    void on_stableStatButton_clicked();
    void on_dynamicStatButton_clicked();
    void on_tableUsersButton_clicked();
    void on_productListButton_clicked();
    void on_createMenButton_clicked();
    void on_addProductButton_clicked();
    void on_exitButton_clicked();

signals:
    void add_product();
};

#endif // MAINWINDOW_H
