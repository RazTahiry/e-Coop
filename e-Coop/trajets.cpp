#include "trajets.h"
#include "dbmanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Trajets::Trajets() : _ref_trajet(""), _lieu_depart(""), _destination(""), _heureMatin(""), _heureSoir("")
{
}

Trajets::Trajets(QString ref_trajet, QString lieu_depart, QString destination, QString heureMatin, QString heureSoir) :
    _ref_trajet(ref_trajet), _lieu_depart(lieu_depart), _destination(destination), _heureMatin(heureMatin), _heureSoir(heureSoir)
{
}

void Trajets::ajout_trajet(QString ref_trajet, QString lieu_depart, QString destination, QString heureMatin, QString heureSoir)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("INSERT INTO TRAJET (refTrajet, lieuDepart, destination, heureMatin, heureSoir) "
                      "VALUES (:refTrajet, :lieuDepart, :destination, :heure)");
        query.bindValue(":refTrajet", ref_trajet);
        query.bindValue(":lieuDepart", lieu_depart);
        query.bindValue(":destination", destination);
        query.bindValue(":heureMatin", heureMatin);
        query.bindValue(":heureSoir", heureSoir);

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

void Trajets::maj_trajet(QString ref_trajet, QString lieu_depart, QString destination, QString heureMatin, QString heureSoir)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("UPDATE TRAJET SET lieuDepart = :lieuDepart, destination = :destination, heure = :heure WHERE refTrajet = :refTrajet");
        query.bindValue(":lieuDepart", lieu_depart);
        query.bindValue(":destination", destination);
        query.bindValue(":heureMatin", heureMatin);
        query.bindValue(":heureSoir", heureSoir);
        query.bindValue(":refTrajet", ref_trajet);

        if(query.exec())
        {
            qDebug() << "Trajet à jour.";
        }
        else
        {
            qDebug() << "Can't update Trajet: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}

void Trajets::supprimer_trajet(QString ref_trajet)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("DELETE FROM TRAJET WHERE refTrajet = :refTrajet");
        query.bindValue(":refTrajet", ref_trajet);

        if(query.exec())
        {
            qDebug() << "Trajet supprimé.";
        }
        else
        {
            qDebug() << "Can't delete Trajet: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}
