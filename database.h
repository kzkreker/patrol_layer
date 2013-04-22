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
    void addGPScordinaes(QString lat,QString lon, QString dateCV,
                         QString speed, QString course,  QString id);

    void closeConnection();
    //void readSettings();
    //void addSettings();
    bool activateConnection();
    void newTable(QString id);
    void createTables();


private:

};

#endif // DATABASE_H
