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

////////////////////////////////////////////////////
///добавление кординат GPS приемника
////////////////////////////////////////////////////

void DataBase::addGPScordinaes(QString GPS, QString dataCV, QString idmain)
{
    QSqlQuery query;

    newTableGPS(idmain);

    //парсим строку
    QStringList gps_data = GPS.split("|");



    if (gps_data.length()==4){

   qDebug()<< gps_data;
    query.exec("insert into vehicle_"+ idmain +" values('"+dataCV+"',"+gps_data[2]+","+gps_data[3]+","+
               idmain+",'"+gps_data[0]+"', '"+gps_data[1]+"')");

//    //исправить костыль
    query.exec("insert into activiti values('18-04-2013 17:32:21',000.0,000.0,"+idmain+",'82.49', '42.49')");

    query.exec("UPDATE activiti SET data='"+dataCV+"', speed="+gps_data[2]+", course="+gps_data[3]+", id="+
                 idmain+", lat='"+gps_data[0]+"', lon='"+gps_data[1]+"' WHERE id="+idmain+";");
    }
}

void DataBase::addPICstatus(QString PIC, QString dataCV, QString idmain)
{
    QSqlQuery query;

    newTablePIC(idmain);

    //парсим строку
    QStringList pic_data = PIC.split("|");
    //добавляем в БД
    if (pic_data.length()==4){

     query.exec( "INSERT INTO vehicle_pic_"+idmain+" (an, led, pot, temp, id, data)"+
                 "VALUES ('{"+pic_data[0]+"}', '{"+pic_data[1]+"}', "+pic_data[2]+","+pic_data[3]+", "+
                idmain+", '"+dataCV+"')");
      }
}

/////////////////////////////////////////////////////////////////
///дрбавление не отосланных кординат
/////////////////////////////////////////////////////////////////
void DataBase::addGPSNotSend(QString GPSstring, QString idmain)
{
    QSqlQuery query;
    //парсим строку
    QStringList gps_data = GPSstring.split("|");

    //обход списка
    foreach(QString gpsline, gps_data){

    //парсим строку
        QStringList gps = gpsline.split("~");

    //добавление записи после проверки её целосности
        if (gps.length()==5) {
             if(gps[0]!="" && gps[1]!="" && gps[2]!="" && gps[3]!="" && gps[4]!=""){
             qDebug()<< gps;
             query.exec("insert into vehicle_"+idmain +" values('"+gps[0]+"',"+gps[1]+","+gps[2]+","+
                       idmain+",'"+gps[3]+"', '"+gps[4]+"')");
            }
        }
    }
}

/////////////////////////////////////////////////////////////////
///сохранение неотосланных показаний датчиков
/////////////////////////////////////////////////////////////////
void DataBase::addPICNotSend(QString PICstring, QString idmain)
{
  QSqlQuery query;
  //парсим строку
  QStringList pic_data = PICstring.split("|");

  //обход списка
  foreach(QString picline, pic_data){

   //парсим строку
   QStringList pic = picline.split("~");

   //добавление записи после проверки её целосности
   if(pic.length()==5){
       qDebug()<< pic;
      if(pic[0]!="" && pic[1]!="" && pic[2]!="" && pic[3]!="" && pic[4]!=""){
          query.exec( "INSERT INTO vehicle_pic_"+idmain+" (an, led, pot, temp, id, data)"+
                   "VALUES ('"+pic[0]+"', '"+pic[1]+"', "+pic[2]+","+pic[3]+", "+
                   idmain+", '"+pic[4]+"')");
          }
       }
   }
}

//////////////////////////////////////////////////
///создание служибных таблиц
//////////////////////////////////////////////////
void DataBase::newTableGPS(QString id)
{
         QSqlQuery query;
         query.exec("CREATE TABLE IF NOT EXISTS  vehicle_"+ id + " ( data timestamp without time zone NOT NULL,"+
                   "speed double precision NOT NULL, course double precision,  id integer NOT NULL,"+
                   "lat character varying(12), lon character varying(12), CONSTRAINT id_key"+ id +" PRIMARY KEY (id , data ))"+
                   "WITH ( OIDS=FALSE); ALTER TABLE vehicle_"+ id +" OWNER TO postgres;");


}

void DataBase::newTablePIC(QString id)
{
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS  vehicle_pic_"+id+" ( an integer[], led integer[], "+
                   "pot integer, temp integer, id integer NOT NULL, data timestamp without time zone NOT NULL, "+
                   "CONSTRAINT id_prim"+id+" PRIMARY KEY (id , data )) WITH (OIDS=FALSE ); ALTER TABLE vehicle_pic_"+id+
                   " OWNER TO postgres");

}

void DataBase::createTables()
{
        QSqlQuery query;
        query.exec("CREATE TABLE  IF NOT EXISTS activiti ( data timestamp without time zone NOT NULL,"
                    "speed double precision NOT NULL,course double precision, id integer NOT NULL,"
                    "lat character varying(12), lon character varying(12),CONSTRAINT id_key_activiti PRIMARY KEY (id))"
                    "WITH (OIDS=FALSE);  ALTER TABLE activiti OWNER TO postgres;");

}
