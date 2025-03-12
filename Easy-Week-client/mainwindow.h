#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "functions_for_client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString login;
    QString password;
    QString email;

public slots:
    void slot_show();
    void set_current_user(QString login, QString password, QString email);
private:
    Ui::MainWindow *ui;

private slots:
    void on_stableStatButton_clicked();
    void on_dynamicStatButton_clicked();
    void on_tableUsersButton_clicked();
};

#endif // MAINWINDOW_H
