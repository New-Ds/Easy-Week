#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QMap>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr); /**< Конструктор */
    ~MyTcpServer(); /**< Деструктор */

public slots:
    /**
     * Слот для обработки нового подключения.
     */
    void slotNewConnection();

    /**
     * Слот для обработки отключения клиента.
     */
    void slotClientDisconnected();

    /**
     * Слот для чтения данных от клиента.
     */
    void slotServerRead();

private:
    QTcpServer * mTcpServer; /**< Сервер для обработки TCP-соединений */
    QTcpSocket * mTcpSocket; /**< Сокет для взаимодействия с клиентом */
    int server_status; /**< Статус сервера */
    QMap<int, QTcpSocket*> mSocketDescriptors; /**< Хранение дескрипторов сокетов */
};

#endif  // MYTCPSERVER_H
