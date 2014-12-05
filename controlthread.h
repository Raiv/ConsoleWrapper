#ifndef CONTROLTHREAD_H
#define CONTROLTHREAD_H

#include <QThread>


class ControlThread : public QThread
{
    Q_OBJECT
public:
    explicit ControlThread(QObject *parent);
    ~ControlThread();
    
};

typedef ControlThread* (*ThreadFactory)(QObject* parent);

#endif // CONTROLTHREAD_H
