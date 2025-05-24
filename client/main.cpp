#include "ui/common/managerforms.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Инициализация менеджера форм и сетевого соединения
    ManagerForms w;
    NetworkSingleton::getInstance();
    
    return a.exec();
}