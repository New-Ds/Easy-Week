#include "func2serv.h"
#include <QString>
#include <QStringList>

using namespace std;
QByteArray parsing(QString input)

{
   QStringList container = input.remove("\r\n").split("//"); //пример входящих данных reg//login_user//password_user
    QString var = container[0];
    if (var == "check_task")
    {
       return check_task();
    }
    else if (var =="auth")
    {
        return auth(container);
    }
    else if (var =="reg")
    {
        return reg();
    }
    else if (var == "get_stat")
    {
        return(get_stat());
    }
    else
    {
        return "server error: unknow command\r\n";
    }
}

QByteArray auth( QStringList log ){
    string res = "You succesfull logged in!\r\nWelcom to system: " + log[1].toStdString() + "\r\nYour password: " + log[2].toStdString()+"\r\n";
    QByteArray byteArray(res.c_str(), res.length());
    return byteArray;
}

QByteArray reg(/*QStringList*/){
    return "you have been successfully registered\r\n";
}

QByteArray get_stat(/*QStringList*/){
    return "Your Statistic: null\r\n";
}

QByteArray check_task(/*QStringList*/){
    return "Task was succesful completed\r\n";
}
