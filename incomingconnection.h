#ifndef INCOMINGCONNECTION_H
#define INCOMINGCONNECTION_H

#include <QObject>
#include <QThread>
#include <QtNetwork/QTcpSocket>

class IncomingConnection : public QObject
{
    Q_OBJECT
public:
    explicit IncomingConnection(int socketId);
private:
    QTcpSocket* socket=NULL;
    int socketId;
signals:
    void hasData(QString data);
    void done(QThread* t);
public slots:
    void sendData(QString data);

private slots:
    void socketHasData();
    void init();
    void close();

};

#endif // INCOMINGCONNECTION_H
