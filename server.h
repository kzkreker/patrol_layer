#ifndef SERVER_H
#define SERVER_H

#include "maiaXmlRpcServer.h"
#include "database.h"
#include "cstatistic.h"
#include "gpsdata.h"

class Server : public QObject {
    Q_OBJECT

    public:
        Server(QObject* parent = 0);

    signals:

    private slots:

         bool curentGPSPICResiv (QString GPSstring, QString PICstring, QString idmain,QString dataCV);
         bool sendNotGPSPICResiv (QString GPSstring, QString PICstring, QString idmain);

    private:
        MaiaXmlRpcServer *server;
        DataBase connector;
        cStatistic status;
};

#endif
