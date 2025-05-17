#ifndef AUTHREGWINDOW_H
#define AUTHREGWINDOW_H

#include <QMainWindow>
#include "functions_for_client.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class AuthRegWindow;
}
QT_END_NAMESPACE

class AuthRegWindow : public QMainWindow
{
    Q_OBJECT

public:
    AuthRegWindow(QWidget *parent = nullptr);
    ~AuthRegWindow();

private slots:
    void on_toRegButton_clicked();

    void on_regButton_clicked();

    void on_loginButton_clicked();

signals:
    void auth_ok(QString id, QString login, QString email);

private:
    Ui::AuthRegWindow *ui;
    void change_type_to_reg(bool);
    void clear();
};
#endif // AUTHREGWINDOW_H
