#include "incomingconnection.h"

IncomingConnection::IncomingConnection(int socketId) :
    QObject(NULL)
{
    this->socketId=socketId;
}


void IncomingConnection::sendData(QString data)
{
    if(socket)
    {
        socket->write(data.toUtf8());
        socket->flush();
    }
}

void IncomingConnection::socketHasData()
{
    if(socket){
        qint64 qt =socket->bytesAvailable ();
        QByteArray data = socket->read(qt);
        QString sData=QString::fromUtf8(data.constData(),data.size());
        emit hasData(sData);
    }}

void IncomingConnection::init()
{
    socket= new QTcpSocket();
    if(socket->setSocketDescriptor(socketId))
    {
        connect(socket,SIGNAL(readyRead()),this,SLOT(socketHasData()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(close()));
        socket->open(QIODevice::ReadWrite);

    }else
    {
        close();
    }
}

void IncomingConnection::close(){
    if(socket)
    {
        socket->close();
    }
    emit done(QThread::currentThread());
    deleteLater();
}
