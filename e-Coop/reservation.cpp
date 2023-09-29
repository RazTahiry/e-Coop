#include "reservation.h"
#include "dbmanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Reservation::Reservation() : _ref_place(""), _cin(""), _nb_place_reserve(0), _membre_famille(""),
    _contact_famille(""), _isPaye(false)
{
}

Reservation::Reservation(QString ref_place, QString nom, QString contact, QString cin,
                         int nb_place_reserve, QString membre_famille, QString contact_famille,
                         QString ref_trajet, QString lieu_depart, QString destination, QString heure_depart, bool isPaye) :
    Identificateur(nom, contact),
    Trajets(ref_trajet, lieu_depart, destination, heure_depart)
{
    this->_ref_place = ref_place;
    this->_cin = cin;
    this->_nb_place_reserve = nb_place_reserve;
    this->_membre_famille = membre_famille;
    this->_contact_famille = contact_famille;
    this->_isPaye = isPaye;
}


void Reservation::reserver(QString ref_place, QString nom, QString contact, QString cin,
                           int nb_place_reserve, QString membre_famille, QString contact_famille, QString ref_trajet,
                           QString lieu_depart, QString destination, QString heure_depart, bool isPaye)
{
    DbManager db(pathToDB);
    if(db.isOpen())
    {
        qDebug() << "Database opened...";

        QSqlQuery query;
        query.prepare("INSERT INTO RESERVATION (refPlace, nomPass, contatPass, cin, nbPlaceReserve, membreFamille, contactFamille, lieuDepart, destination, isPaye) "
                      "VALUES (:refPlace, :nomPass, :contactPass, :cin, :nbPlaceReserve, :membreFamille, :contactFamille, :lieuDepart, :destination, :isPaye)");
        query.bindValue(":refPlace", ref_place);
        query.bindValue(":nomPass", nom);
        query.bindValue(":contactPass", contact);
        query.bindValue(":cin", cin);
        query.bindValue(":nbPlaceReserve", nb_place_reserve);
        query.bindValue(":membreFamille", membre_famille);
        query.bindValue(":contactFamille", contact_famille);
        query.bindValue(":lieuDepart", lieu_depart);
        query.bindValue(":destination", destination);
        query.bindValue(":isPaye", isPaye);

        if(query.exec())
        {
            qDebug() << "Reservation added.";
        }
        else
        {
            qDebug() << "Reservation not added: " << query.lastError();
        }
    }
    else
    {
        qDebug() << "Database not opened.";
    }
}

