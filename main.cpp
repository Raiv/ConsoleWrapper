#include <QCoreApplication>
#include "multithreadtcpserver.h"
#include "consolewrapper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    MultithreadTcpServer server;

    QStringList args = QCoreApplication::arguments();

    int pos = args.indexOf("-port");
    if((pos>=0)&&(pos<args.size()-1))
    {
        server.listen(args[pos+1].toInt());
    }
    else
    {
    }

    ConsoleWrapper* wrapper=NULL;

    pos = args.indexOf("-exe");
    if((pos>=0)&&(pos<args.size()-1))
    {
        wrapper= new ConsoleWrapper(args[pos+1]);
    }

    if(wrapper){
        QObject::connect(wrapper,SIGNAL(out(QString)),&server,SIGNAL(in(QString)));
        QObject::connect(&server,SIGNAL(out(QString)),wrapper,SLOT(in(QString)));
    }





    return a.exec();
}
