

#include "multithreadtcpserver.h"
#include "incomingconnection.h"


#include <QTcpServer>
#include <QTcpSocket>
#include <QVariant>
#include <QDebug>
#include <QThread>




MultithreadTcpServer::MultithreadTcpServer(ThreadFactory factory)
    : QTcpServer()
    ,serverDomain("localhost")
    ,threadPool(factory,this)
{

}

MultithreadTcpServer::~MultithreadTcpServer()
{

    if(this->isListening())
    this->close();

    cleanupThreads();
}



void MultithreadTcpServer::cleanupThreads()// removes all threads from all lists
{
    emit closeAll();

}

void MultithreadTcpServer::incomingConnection(int socketDescriptor)
{

   // Q_ASSERT(requestHandler);

        QThread* t = threadPool.reserveThread();

        IncomingConnection * connection = new IncomingConnection(socketDescriptor);

        connect(connection, SIGNAL(done(QThread*)) , &threadPool,SLOT(returnThread(QThread*)),Qt::QueuedConnection);
        connect(this, SIGNAL(closeAll()) , connection,SLOT(close()),Qt::QueuedConnection);


        connection->moveToThread(t);
        connection->metaObject()->invokeMethod(connection,"init",Qt::QueuedConnection); // direct call to init in object's new thread.

        connect(connection, SIGNAL(hasData(QString)) , this,SIGNAL(out(QString)),Qt::QueuedConnection);
        connect(this, SIGNAL(in(QString)) , connection,SLOT(sendData(QString)),Qt::QueuedConnection);
}


void MultithreadTcpServer::setServerDomain(QString sdmn)
{
    serverDomain=sdmn;
}

QString MultithreadTcpServer::getServerDomain()
{
     return serverDomain;
}


bool MultithreadTcpServer::listen(quint16 port)
{
    return QTcpServer::listen(QHostAddress::Any, port);
}
