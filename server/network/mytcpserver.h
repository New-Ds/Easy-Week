#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QMap>

class RequestHandler;

/**
 * @brief Класс TCP-сервера для обработки клиентских соединений
 */
class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор сервера
     * @param parent Родительский объект
     */
    explicit MyTcpServer(QObject *parent = nullptr);
    
    /**
     * @brief Деструктор сервера
     */
    ~MyTcpServer();

public slots:
    /**
     * @brief Обработка нового соединения
     */
    void slotNewConnection();
    
    /**
     * @brief Обработка отключения клиента
     */
    void slotClientDisconnected();
    
    /**
     * @brief Обработка входящих данных
     */
    void slotServerRead();

private:
    QTcpServer* mTcpServer;                  ///< Объект TCP-сервера
    QMap<int, QTcpSocket*> mSocketDescriptors; ///< Хранение дескрипторов сокетов
    int server_status;                        ///< Статус сервера
    RequestHandler* mRequestHandler;         ///< Обработчик запросов
};
#endif  // MYTCPSERVER_H