#include "singleton.h"

NetworkSingleton* NetworkSingleton::p_instance = nullptr;
NetworkSingletonDestroyer NetworkSingleton::destroyer;

NetworkSingletonDestroyer::~NetworkSingletonDestroyer() {
    if (p_instance) {
        delete p_instance;
        p_instance = nullptr;
    };
};

NetworkSingleton& NetworkSingleton::getInstance() {
    if (!p_instance) {
        p_instance = new NetworkSingleton();
        destroyer.initialize(p_instance);
    };
    return *p_instance;
}

void NetworkSingletonDestroyer::initialize(NetworkSingleton* p) {
    this->p_instance = p;
};

NetworkSingleton::NetworkSingleton() {
    socket = new QTcpSocket(this);

    // т.к. запускаю на своём пк адрес localhost, в будущем заменить на ip сервера
    socket->connectToHost("localhost", 33333);

    // проверка успешного подключения к серверу
    if (socket->waitForConnected()) {
        qDebug() << "Connected to server!";
    } else {
        qDebug() << "Failed to connect to server:" << socket->errorString();
    }

    connect(socket, &QTcpSocket::connected, this, &NetworkSingleton::slotConnected);

    // Почему вы так жестоко с нами обошлись
    // connect(socket, &QTcpSocket::readyRead, this, &NetworkSingleton::slotReadyRead);
};

NetworkSingleton::~NetworkSingleton() {
    socket->close();
};

QByteArray NetworkSingleton::sendMessage(QStringList params)
{
    qDebug() << "=== CLIENT DEBUG START ===";
    qDebug() << "Sending message:" << params;

    if (socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "Error: Not connected to server!";
        return "Error: Not connected to server!";
    }

    QString message = params.join("//");
    QByteArray data = message.toUtf8();

    qDebug() << "Formatted message:" << message;
    qDebug() << "Data to send:" << data;

    qint64 bytesWritten = socket->write(data);
    qDebug() << "Bytes written:" << bytesWritten;

    // Архитектурное решение: увеличенный timeout для диагностики
    const int WRITE_TIMEOUT = 10000; // 10 секунд
    const int READ_TIMEOUT = 30000;  // 30 секунд для тяжелых операций с БД

    if (!socket->waitForBytesWritten(WRITE_TIMEOUT)) {
        qDebug() << "Write timeout after" << WRITE_TIMEOUT << "ms";
        return "Error: Write timeout";
    }

    qDebug() << "Write completed, waiting for response...";

    if (!socket->waitForReadyRead(READ_TIMEOUT)) {
        qDebug() << "Read timeout after" << READ_TIMEOUT << "ms";
        qDebug() << "Socket state:" << socket->state();
        qDebug() << "Socket error:" << socket->errorString();
        return "Error: Read timeout";
    }

    QByteArray res;
    // Читаем все доступные данные с небольшими паузами
    int attempts = 0;
    while (socket->bytesAvailable() > 0 || attempts < 3) {
        if (socket->bytesAvailable() == 0) {
            // Даем серверу время отправить данные
            QThread::msleep(100);
            attempts++;
            continue;
        }

        QByteArray chunk = socket->readAll();
        qDebug() << "Received chunk:" << chunk.size() << "bytes";
        res.append(chunk);
        attempts = 0; // Сбрасываем счетчик при получении данных
    }

    qDebug() << "Total response:" << res.size() << "bytes";
    qDebug() << "Response preview:" << res.left(100);
    qDebug() << "=== CLIENT DEBUG END ===";

    if (res.isEmpty()) {
        return "Error: empty response from server";
    }

    return res;
}

void NetworkSingleton::slotConnected() {
    qDebug() << "Connected to server!";
}

void NetworkSingleton::slotReadyRead() {
    QByteArray data = socket->readAll();
    qDebug() << "Data received:" << data;
}
