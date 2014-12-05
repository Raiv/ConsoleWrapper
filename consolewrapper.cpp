#include "consolewrapper.h"
#include <QTextStream>
#include <stdio.h>

ConsoleWrapper::ConsoleWrapper(QString args, QObject *parent) :
    QObject(parent),m_args(args),process(this)
{


    connect(&process,SIGNAL(readyRead()),this,SLOT(dataReady()));
//    connect(&process,SIGNAL(readyReadStandardError()),this,SLOT(dataReadyError()));

    connect(&process,SIGNAL(finished(int, QProcess::ExitStatus)),this,SLOT(terminated()));
    process.setReadChannel(QProcess::StandardOutput);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(m_args);
}


void ConsoleWrapper::dataReady()
{
    QString data;
    if(process.bytesAvailable()>0)
    {
        data=process.read(process.bytesAvailable());
    }
    QTextStream(stdout) << data;
    emit out(data);
}


void  ConsoleWrapper::in(QString data)
{
    if(process.isOpen())
    {
        process.write(data.toUtf8());
    }
}


void ConsoleWrapper::terminated()
{
    QTextStream(stdout) << "Error launching process"+process.error();
    emit terminated();

}

 ConsoleWrapper::~ConsoleWrapper(){
    if(process.isOpen())
    {
        process.kill();
    }
}
