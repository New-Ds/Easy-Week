#include <QCoreApplication>
#include "mytcpserver.h"
#include "databasesingleton.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Инициализация БД
    DataBaseSingleton* db = DataBaseSingleton::getInstance();
    if (!db->initialize("Easyweek.db")) {
        qFatal("Failed to initialize database");
    }

    MyTcpServer myserv;
    return a.exec();
}
