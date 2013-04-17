#include "server.h"

Server::Server(QObject* parent) : QObject(parent) {

    server = new MaiaXmlRpcServer(8082, this);
    server->addMethod("examples.nix", this, "nix");
    server->addMethod("transport.curentGPSResiv", this, "curentGPSResiv");
    connector.activateConnection();

}

///////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////
void Server::nix() {
    qDebug() << "i got called";
}

////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////
bool Server::curentGPSResiv(QString lat, QString lon,QString dateCV, QString speed, QString course, QString id)
{
    qDebug()<<dateCV;
    qDebug()<<id;
    connector.addGPScordinaes(lat,lon, dateCV, speed,course , id);
    return true;
}
