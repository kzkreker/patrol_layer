#include "server.h"

////////////////////////////////////////////////////////
///конструктор сервера
////////////////////////////////////////////////////////
Server::Server(QObject* parent) : QObject(parent) {

    server = new MaiaXmlRpcServer(8082, this);

    server->addMethod("transport.curentGPSPICResiv", this, "curentGPSPICResiv");
    server->addMethod("transport.sendNotGPSPICResiv", this, "sendNotGPSPICResiv");
    connector.activateConnection();
    connector.createTables();
}

////////////////////////////////////////////////////////
///прием кординат и показаний датчиков от клиентов
////////////////////////////////////////////////////////
bool Server:: curentGPSPICResiv(QString GPSstring, QString PICstring, QString idmain,QString dataCV)
{
    if (GPSstring!="fail" ){
    connector.addGPScordinaes(GPSstring,dataCV,idmain);}
    if (PICstring!="fail" ){
    connector.addPICstatus(PICstring,dataCV,idmain);}

    return true ;
}

///////////////////////////////////////////////////////
//обработка не отправленных показаний
///////////////////////////////////////////////////////
bool Server:: sendNotGPSPICResiv(QString GPSstring, QString PICstring, QString idmain)
{
    connector.addGPSNotSend(GPSstring, idmain);
    connector.addPICNotSend(PICstring, idmain);

    return true;
}
