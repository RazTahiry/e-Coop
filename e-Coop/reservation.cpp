#include "reservation.h"
#include "dbmanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Reservation::Reservation() : _ref_place(""), _cin(""), _membre_famille(""),
    _contact_famille(""), _date_voyage(""), _isPaye(false)
{
}

Reservation::Reservation(QString ref_place, QString nom, QString contact, QString cin,
                         int nb_Place, QString membre_famille, QString contact_famille, QString num_Matriculation,
                         QString ref_trajet, QString date_voyage, QString lieu_depart, QString destination,
                         QString heureMatin, QString heureSoir, bool isPaye, int decalage) :
    Vehicule(num_Matriculation, nom, contact, ref_trajet,lieu_depart, destination, heureMatin, heureSoir, nb_Place, decalage)
{
    this->_ref_place = ref_place;
    this->_cin = cin;
    this->_membre_famille = membre_famille;
    this->_contact_famille = contact_famille;
    this->_date_voyage = date_voyage;
    this->_isPaye = isPaye;
}

bool Reservation::reserver(QString ref_place, QString nom, QString contact, QString cin,
                           int nb_place_reserve, QString membre_famille, QString contact_famille, QString num_Matriculation,
                           QString ref_trajet, QString date_voyage, QString heure_depart, bool isPaye)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("INSERT INTO PASSAGER (refPlace, nomPass, contactPass, cin, nbPlaceReserve, membreFamille, contactFamille, voiture, refTrajet, dateVoyage, heureDepart, isPaye) "
                      "VALUES (:refPlace, :nomPass, :contactPass, :cin, :nbPlaceReserve, :membreFamille, :contactFamille, :voiture, :refTrajet, :dateVoyage, :heureDepart, :isPaye)");
        query.bindValue(":refPlace", ref_place);
        query.bindValue(":nomPass", nom);
        query.bindValue(":contactPass", contact);
        query.bindValue(":cin", cin);
        query.bindValue(":nbPlaceReserve", nb_place_reserve);
        query.bindValue(":membreFamille", membre_famille);
        query.bindValue(":contactFamille", contact_famille);
        query.bindValue(":voiture", num_Matriculation);
        query.bindValue(":refTrajet", ref_trajet);
        query.bindValue(":dateVoyage", date_voyage);
        query.bindValue(":heureDepart", heure_depart);
        query.bindValue(":isPaye", isPaye);

        if(query.exec())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

