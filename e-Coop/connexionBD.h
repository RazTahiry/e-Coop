#ifndef CONNEXIONBD_H
#define CONNEXIONBD_H

#include "QSqlDatabase"
#include "QSqlQuery"

static bool connectingDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("testbd");
    db.setPort(3306);
    db.setPassword("");

    if(db.open())
    {
        return true;
    }
    else
    {
        return  false;
    }
}

#endif // CONNEXIONBD_H
