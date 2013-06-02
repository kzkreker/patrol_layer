#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include <QDebug>
#include <QDate>
#include "database.h"
#include "gpsdata.h"
class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    
signals:

public slots:
    //обработка приема текущих кординрат
    void addGPScordinaes(QString GPS,QString dataCV, QString idmain);
    void addPICstatus(QString PIC,QString dataCV, QString idmain);

    //обработка приема не обправленных данных
    void addPICNotSend(QString PICstring, QString  idmain);
    void addGPSNotSend(QString GPSstring, QString  idmain);

    void closeConnection();
    //void readSettings();
    //void addSettings();

    //обслуживающие функции
    bool activateConnection();
    void newTableGPS(QString id);
    void newTablePIC(QString id);
    void createTables();


private:

};

#endif // DATABASE_H
