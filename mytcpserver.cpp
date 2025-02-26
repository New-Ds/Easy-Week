#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include<QString>
#include "func2serv.h"
MyTcpServer::~MyTcpServer()
{

    mTcpServer->close();
    //server_status=0;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        //server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
 //   if(server_status==1){
        mTcpSocket = mTcpServer->nextPendingConnection();
        mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
        connect(mTcpSocket, &QTcpSocket::readyRead,this,&MyTcpServer::slotServerRead);
        connect(mTcpSocket,&QTcpSocket::disconnected,this,&MyTcpServer::slotClientDisconnected);
   // }
}

void MyTcpServer::slotServerRead(){
    QString res = "";
    QByteArray array;// =mTcpSocket->readAll();
    while(mTcpSocket->bytesAvailable()>0)
    {
        array =mTcpSocket->readAll();
        /*if(array=="\x01")
        {
            mTcpSocket->write(res.toUtf8());
            res = "";
        }
        else*/
        res.append(array);
    }
    qDebug()<<"server"<<res;
    mTcpSocket->write(parsing(res));

}

void MyTcpServer::slotClientDisconnected(){
    mTcpSocket->close();
}
