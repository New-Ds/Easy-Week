#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>
#include "func2serv.h"

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    server_status = 0;
    qDeleteAll(mSocketDescriptors); // Удаляем все сокеты
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "server is not started";
    } else {
        server_status = 1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection()
{
    if (server_status == 1) {
        QTcpSocket *clientSocket = mTcpServer->nextPendingConnection();
        int socketDescriptor = clientSocket->socketDescriptor(); // Получаем дескриптор сокета

        if (socketDescriptor == -1) {
            qDebug() << "Invalid socket descriptor!";
            clientSocket->deleteLater(); // Удаляем сокет, если дескриптор недействителен
            return;
        }

        mSocketDescriptors.insert(socketDescriptor, clientSocket); // Сохраняем сокет в контейнере

        qDebug() << "New connection, socket descriptor:" << socketDescriptor;

        connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
    }
}

void MyTcpServer::slotServerRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QByteArray data = clientSocket->readAll();
    qDebug() << "Received data:" << data;

    // Обрабатываем данные сразу, без накопления
    QByteArray response = parsing(QString(data).trimmed(), clientSocket->socketDescriptor());
    clientSocket->write(response);
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) {
        return;
    }

    // Получаем дескриптор сокета из контейнера
    int socketDescriptor = -1;
    for (auto it = mSocketDescriptors.begin(); it != mSocketDescriptors.end(); ++it) {
        if (it.value() == clientSocket) {
            socketDescriptor = it.key();
            break;
        }
    }

    if (socketDescriptor != -1) {
        mSocketDescriptors.remove(socketDescriptor); // Удаляем сокет из контейнера
        qDebug() << "Client disconnected, socket descriptor:" << socketDescriptor;
    } else {
        qDebug() << "Client disconnected, but socket descriptor not found!";
    }

    clientSocket->deleteLater(); // Удаляем сокет
}
