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
    if (!clientSocket) {
        qDebug() << "CRITICAL ERROR: Invalid socket in slotServerRead";
        return;
    }

    QByteArray data = clientSocket->readAll();

    // Архитектурное решение: детальное логирование для диагностики
    qDebug() << "\n=== SERVER REQUEST PROCESSING ===";
    qDebug() << "Socket descriptor:" << clientSocket->socketDescriptor();
    qDebug() << "Received bytes:" << data.size();
    qDebug() << "Raw data:" << data;
    qDebug() << "As string:" << QString(data);

    // Техническое решение: валидация данных перед обработкой
    if (data.isEmpty()) {
        qDebug() << "WARNING: Empty data received";
        return;
    }

    // Обработка запроса
    QString trimmedInput = QString(data).trimmed();
    qDebug() << "Processing command:" << trimmedInput;

    QByteArray response = parsing(trimmedInput, clientSocket->socketDescriptor());

    qDebug() << "Response size:" << response.size();
    qDebug() << "Response preview:" << response.left(100);

    // КРИТИЧЕСКИ ВАЖНО: правильная отправка данных
    if (!response.isEmpty()) {
        qint64 bytesWritten = clientSocket->write(response);
        qDebug() << "Bytes written:" << bytesWritten;

        // Архитектурное решение: гарантированная отправка данных
        if (bytesWritten > 0) {
            // КРИТИЧЕСКИ ВАЖНО: форсируем отправку
            clientSocket->flush();
            qDebug() << "Data flushed successfully";

            // Дополнительная проверка состояния сокета
            if (clientSocket->state() == QTcpSocket::ConnectedState) {
                qDebug() << "Socket still connected after write";
            } else {
                qDebug() << "WARNING: Socket state changed:" << clientSocket->state();
            }
        } else {
            qDebug() << "ERROR: Failed to write response";
        }
    } else {
        qDebug() << "WARNING: Empty response from parsing";
        // Отправляем пустой JSON массив как fallback
        clientSocket->write("[]");
        clientSocket->flush();
    }

    qDebug() << "=== SERVER REQUEST COMPLETE ===\n";
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
