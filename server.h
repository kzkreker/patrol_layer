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
        void nix();
        bool curentGPSResiv(QString lat, QString lon, QString time,
                           QString dateCV, QString course, QString id);

    private:
        MaiaXmlRpcServer *server;
        DataBase connector;
        cStatistic status;
};

#endif
