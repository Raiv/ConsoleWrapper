/*
 * Copyright 2011 Nikhil Marathe <nsm.nikhil@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE. 
 */

#ifndef Q_HTTP_SERVER
#define Q_HTTP_SERVER

#define QHTTPSERVER_VERSION_MAJOR 0
#define QHTTPSERVER_VERSION_MINOR 2
#define QHTTPSERVER_VERSION_PATCH 0

#include <QObject>
#include <QHostAddress>
#include <QList>
#include <QTcpServer>

//class QTcpServer;
#include "threadpoolwithsignals.h"



//class ThreadPoolWithSignals;



class MultithreadTcpServer : public QTcpServer
{
    Q_OBJECT

public:

    MultithreadTcpServer(ThreadFactory factory=NULL);
    void setServerDomain(QString sdmn);
    QString getServerDomain();
    virtual ~MultithreadTcpServer();


    bool listen(quint16 port);

signals:
    void in(QString);
    void out(QString);

    void closeAll();
protected:
     void incomingConnection(int socketDescriptor);
     QString serverDomain;
private:

    QThread* getIdleThread(); // gets thread from inactive threads if any available or creates new


    void cleanupThreads();// removes all threads from all lists


private:
  ThreadPoolWithSignals threadPool;


};

#endif
