#include "Singleton.h"

ClientSingleton * ClientSingleton::p_instance;
ClientSingletonDestroyer ClientSingleton::destroyer;

ClientSingletonDestroyer::~ClientSingletonDestroyer() {
    if (p_instance) {
        delete p_instance;
        p_instance = nullptr;
    };
};

ClientSingleton& ClientSingleton::getInstance() {

    if (!p_instance) {
        p_instance = new ClientSingleton();
        destroyer.initialize(p_instance);
    };
    return *p_instance;
}


void ClientSingletonDestroyer::initialize(ClientSingleton* b) {
    this->p_instance = b;
};


ClientSingleton::ClientSingleton() {
    socket = new QTcpSocket(this);

    // т.к. запускаю на своём пк адрес localhost, в будущем заменить на ip сервера
    socket->connectToHost("localhost", 33333);

    // проверка успешного подключения к серверу
    if (socket->waitForConnected()) {
        qDebug() << "Connected to server!";
    } else {
        qDebug() << "Failed to connect to server:" << socket->errorString();
    }



    //connect(socket, SIGNAL(connected()), SLOT(slot_connected()));
    //connect(socket, SIGNAL(readyRead()), SLOT(slot_readyRead()));



};
ClientSingleton::~ClientSingleton() {
    socket->close();

};

QByteArray ClientSingleton::send_msg(QStringList msg)
{

    if (socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "Error: Not connected to server!";
        return "Error: Not connected to server!";
    }


    QString message = msg.join("//");
    QByteArray data = message.toUtf8();

    socket->write(data);
    socket->waitForReadyRead(5000); // таймаут 5 сек



    QByteArray res = "";
    while (socket->bytesAvailable() > 0) {
        QByteArray array = socket->readAll();
        //qDebug() << array << "\n";
        if (array == "\\x01\r\n") {
            socket->write(res);
            res = "";
        } else {
            res.append(array);
        }
    }

    if (res.isEmpty()) {
        //qDebug() << "Error: empty response from server";
        return "Error: empty response from server";
    }
    return res;

}

void ClientSingleton::slot_connected() {
    qDebug() << "Connected to server!";
}

void ClientSingleton::slot_readyRead() {
    QByteArray data = socket->readAll();
    qDebug() << "Data received:" << data;
}
