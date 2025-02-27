#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>
#include "func2serv.h"

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    server_status = 0;
    qDeleteAll(mTcpSockets); // Удаляем все сокеты
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

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
        mTcpSockets.append(clientSocket); // Добавляем сокет в список

        clientSocket->write("Hello, World!!! I am echo server!\r\n");

        connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
    }
}

void MyTcpServer::slotServerRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender()); // Получаем сокет, который отправил сигнал
    if (!clientSocket) {
        return;
    }

    QString res = "";
    while (clientSocket->bytesAvailable() > 0) {
        QByteArray array = clientSocket->readAll();
        qDebug() << array << "\n";
        if (array == "\x01") {
            clientSocket->write(res.toUtf8());
            res = "";
        } else {
            res.append(array);
        }
    }
    clientSocket->write(parsing(res));
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender()); // Получаем сокет, который отправил сигнал
    if (!clientSocket) {
        return;
    }

    mTcpSockets.removeOne(clientSocket); // Удаляем сокет из списка
    clientSocket->deleteLater(); // Удаляем сокет
}
