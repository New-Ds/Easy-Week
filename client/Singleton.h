#ifndef SINGLETON_H
#define SINGLETON_H
#include <QObject>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QStringList>


class ClientSingleton;


class ClientSingletonDestroyer {
    private:
        ClientSingleton * p_instance;
    public:
        ~ClientSingletonDestroyer();
        void initialize(ClientSingleton * p);
};



class ClientSingleton : public QObject
{
    Q_OBJECT
private:
    static ClientSingleton * p_instance;
    static ClientSingletonDestroyer destroyer;
    QTcpSocket* socket;
protected:
    ClientSingleton(); //соед с сервером
    ~ClientSingleton(); // закрыть соед
    ClientSingleton(const ClientSingleton&) = delete;
    ClientSingleton& operator=(const ClientSingleton&) = delete;

    friend class ClientSingletonDestroyer;

public:
    static ClientSingleton& getInstance();
    QByteArray send_msg(QStringList);
public slots:
    void slot_connected();
    void slot_readyRead();
};







#endif // SINGLETON_H
