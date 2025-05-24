#include "requesthandler.h"
#include "../services/authservice.h"
#include "../services/productservice.h"
#include "../services/rationservice.h"
#include "../services/statsservice.h"
#include <QDebug>

RequestHandler::RequestHandler(QObject *parent) : QObject(parent)
{
    m_authService = new AuthService(this);
    m_productService = new ProductService(this);
    m_rationService = new RationService(this);
    m_statsService = new StatsService(this);
}

RequestHandler::~RequestHandler()
{
    // QObject автоматически удалит дочерние объекты
}

QByteArray RequestHandler::handleRequest(const QByteArray& data, int socketDescriptor)
{
    // Архитектурное решение: нормализация входных данных
    QString input = QString::fromUtf8(data);
    QStringList container = input.remove("\r\n").split("//");

    if (container.isEmpty()) {
        qDebug() << "ERROR: Empty command received";
        return "server error: empty command\r\n";
    }

    // Диагностика для отладки маршрутизации
    qDebug() << "=== PARSING REQUEST ===";
    qDebug() << "Socket:" << socketDescriptor;
    qDebug() << "Raw input:" << input;
    qDebug() << "Parsed command:" << container;
    qDebug() << "Command[0]:" << (container.size() > 0 ? container[0] : "NONE");
    qDebug() << "Command[1]:" << (container.size() > 1 ? container[1] : "NONE");

    QString command = container[0];

    // Маршрутизация запроса к соответствующему сервису
    if (command == "admin") {
        if (container.size() < 2) {
            qDebug() << "ERROR: Admin command without subcommand";
            return "server error: admin command requires subcommand\r\n";
        }

        QString adminCmd = container[1];
        qDebug() << "Admin subcommand:" << adminCmd;

        if (adminCmd == "get_all_users") {
            return m_authService->getAllUsers();
        }
        else if (adminCmd == "dynamic_stat") {
            return m_statsService->getDynamicStats();
        }
        else if (adminCmd == "stable_stat") {
            return m_statsService->getStableStats();
        }
        else {
            qDebug() << "Unknown admin command:" << adminCmd;
            return "server error: unknown admin command\r\n";
        }
    }
    else if (command == "check_task") {
        return "Task was succesful completed\r\n";
    }
    else if (command == "auth") {
        return m_authService->authenticateUser(container);
    }
    else if (command == "add_product") {
        return m_productService->addProduct(container);
    }
    else if (command == "user" && container.size() >= 3) {
        if (container[2] == "get_products") {
            return m_productService->getProductsByUser(container[1]);
        }
        else if (container[2] == "add_favorite_ration") {
            return m_rationService->addFavoriteRation(container);
        }
    }
    else if (command == "reg") {
        return m_authService->registerUser(container);
    }
    else if (command == "get_stat") {
        return m_statsService->getStatistics();
    }
    else if (command == "menu_export") {
        return "Меню успешно экспортировано!\r\n";
    }
    else {
        qDebug() << "ERROR: Unknown command:" << command;
        return "server error: unknown command\r\n";
    }
    
    return "Error: Request not processed\r\n";
}