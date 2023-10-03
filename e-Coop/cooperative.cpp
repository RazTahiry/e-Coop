#include "cooperative.h"
#include "dbmanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Cooperative::Cooperative()
{
    this->_ref_coop = "";
    this->_address = "";
}

Cooperative::Cooperative(QString ref_coop, QString nom,
                         QString contact, QString address):
    Identificateur(nom, contact)
{
    this->_ref_coop = ref_coop;
    this->_address = address;
}

void Cooperative::majCoop(QString nom, QString contact, QString address)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("UPDATE COOPERATIVE SET nomCoop = :nom, adresseCoop = :adresse, contactCoop = :contact WHERE refCoop = 1");
        query.bindValue(":nom", nom);
        query.bindValue(":contact", contact);
        query.bindValue(":adresse", address);

        if(query.exec())
        {
            qDebug() << "data added.";
        }
        else
        {
            qDebug() << "data not added: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}

void Cooperative::reinitialiser()
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.exec("UPDATE COOPERATIVE SET nomCoop = '', adresseCoop = '', contactCoop = '' WHERE refCoop = 1");
        query.exec("DELETE FROM VEHICULE");
        query.exec("DELETE FROM TRAJET");
        query.exec("DELETE FROM RESERVATION");

        if(query.exec())
        {
            qDebug() << "Cooperative réinitialisée.";
        }
        else
        {
            qDebug() << "Can't reset Coopérative: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}
