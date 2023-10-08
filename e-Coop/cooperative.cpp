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

Cooperative::Cooperative(QString ref_coop, QString nom, QString contact,
                         QString contact1, QString contact2, QString address, QString datePremierVoyage):
    Identificateur(nom, contact)
{
    this->_ref_coop = ref_coop;
    this->_address = address;
    this->_contact1 = contact1;
    this->_contact2 = contact2;
    this->_datePremierVoyage = datePremierVoyage;
}

void Cooperative::majCoop(QString nom, QString contact, QString contact1, QString contact2, QString address, QString datePremierVoyage)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("UPDATE COOPERATIVE SET nomCoop = :nom, adresseCoop = :adresse, contactCoop = :contact, contact1Coop = :contact1, contact2Coop = :contact2, datePremierVoyage = :date WHERE refCoop = 1");
        query.bindValue(":nom", nom);
        query.bindValue(":contact", contact);
        query.bindValue(":contact1", contact1);
        query.bindValue(":contact2", contact2);
        query.bindValue(":adresse", address);
        query.bindValue(":date", datePremierVoyage);

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
        query.exec("DELETE FROM GESTION");

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
