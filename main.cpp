#include "managerforms.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    ManagerForms w;
    ClientSingleton::getInstance();
    return a.exec();
}
