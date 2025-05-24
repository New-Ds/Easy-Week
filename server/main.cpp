#include <QCoreApplication>
#include <QObject>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "network/mytcpserver.h"
#include "database/databasesingleton.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Инициализация БД
    DataBaseSingleton* db = DataBaseSingleton::getInstance();
    if (!db->initialize("../../Easyweek.db")) {
        qFatal("Failed to initialize database");
    }

    // Создание и запуск TCP-сервера
    MyTcpServer myserv;
    
    return a.exec();
}