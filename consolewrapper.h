#ifndef CONSOLEWRAPPER_H
#define CONSOLEWRAPPER_H

#include <QObject>
#include <QProcess>

class ConsoleWrapper : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleWrapper(QString args,QObject *parent = 0);
    virtual ~ConsoleWrapper();
signals:
    void out(QString);
    void dead();
public slots:
    void in(QString data);
private slots:
    void dataReady();

    void terminated();
private:
    QString m_args;
    QProcess process;
};

#endif // CONSOLEWRAPPER_H
