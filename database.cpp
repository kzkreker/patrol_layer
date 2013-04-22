#include "database.h"


DataBase::DataBase(QObject *parent) :
    QObject(parent)
{
}

 QSqlDatabase db;


bool DataBase::activateConnection()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("GPStrack");
    db.setHostName("localhost");
    db.setPort(1254);
    db.setUserName("postgres");

    if (!db.open()) {
        qDebug() << QObject::trUtf8("Error") << db.lastError().text();
        return -1;
    }

    return true;
}

void DataBase::closeConnection(){
    db.close();
}

void DataBase::addGPScordinaes(QString lat,QString lon,
                               QString dateCV,  QString speed, QString course,QString id)
{
    QSqlQuery query;

    newTable(id);

    query.exec("insert into vehicle_"+ id +" values('"+dateCV+"',"+speed+","+course+","+
               id+",'"+lat+"', '"+lon+"')");

    query.exec("insert into activiti values('18-04-2013 17:32:21',000.0,000.0,"+id+",'82.49', '42.49')");

    query.exec("UPDATE activiti SET data='"+dateCV+"', speed="+speed+", course="+course+", id="+
                 id+", lat='"+lat+"', lon='"+lon+"' WHERE id="+id+";");
}

void DataBase::newTable(QString id)
{
      QSqlQuery query;
      query.exec("CREATE TABLE IF NOT EXISTS  vehicle_"+ id + " ( data timestamp without time zone NOT NULL,"+
               "speed double precision NOT NULL, course double precision,  id integer NOT NULL,"+
               "lat character varying(12), lon character varying(12), CONSTRAINT id_key"+ id +" PRIMARY KEY (id , data ))"+
               "WITH ( OIDS=FALSE); ALTER TABLE vehicle_"+ id +" OWNER TO postgres;");
}



void DataBase::createTables()
{
    QSqlQuery query;
    query.exec("CREATE TABLE  IF NOT EXISTS activiti ( data timestamp without time zone NOT NULL,"
                "speed double precision NOT NULL,course double precision, id integer NOT NULL,"
                "lat character varying(12), lon character varying(12),CONSTRAINT id_key_activiti PRIMARY KEY (id))"
                "WITH (OIDS=FALSE);  ALTER TABLE activiti OWNER TO postgres;");

}
