#ifndef THREADPOOLWITHSIGNALS_H
#define THREADPOOLWITHSIGNALS_H

#include <QObject>

#include <QSet>
#include <QTimer>
#include <QMutex>
#include "controlthread.h"

//class QThread;
//class ControlThread;



class ThreadPoolWithSignals : public QObject
{
    Q_OBJECT
public:
    explicit ThreadPoolWithSignals(ThreadFactory factory,QObject *parent = 0);
    virtual ~ThreadPoolWithSignals();
     QThread* reserveThread();
public slots:

    void returnThread( QThread* ); // removes thread from active threads and adds it to inactive.
private:
    ThreadFactory tFactory;
    // deletes thread from inactive threads if any available.
    // void setThreadActive( QThread* ); // adds thread to active threads.
    QTimer cleanupTimer;
   // QMutex threadMutex;
    //QScopedPointer<ControlThread> control;
    void cleanupThreads();// removes all threads from all lists
 private slots:
    void cleanupIdleThreads(); // removes, if any, all threads which are unused, left reserved threads only

private:
    QSet<QThread*> activeThreads;
    QSet<QThread*> idleThreads;
    QSet<QThread*> allThreads;
};





#endif // THREADPOOLWITHSIGNALS_H
