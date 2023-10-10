#ifndef RESERVATION_H
#define RESERVATION_H

#include "vehicule.h"

class Reservation : public Vehicule
{
    public:
        Reservation();
        Reservation(QString ref_place, QString nom, QString contact, QString cin,
                    int nb_Place, QString membre_famille, QString contact_famille, QString num_Matriculation,
                    QString ref_trajet, QString date_voyage, QString lieu_depart, QString destination,
                     QString heureMatin, QString heureSoir, bool isPaye, int decalage);

        bool reserver(QString ref_place, QString nom, QString contact, QString cin, int nb_place_reserve,
                      QString membre_famille, QString contact_famille, QString num_Matriculation,
                      QString ref_trajet, QString date_voyage, QString heure_depart, bool isPaye);

    private:
        QString _ref_place;
        QString _cin;
        QString _membre_famille;
        QString _contact_famille;
        QString _date_voyage;
        bool _isPaye;
};

#endif // RESERVATION_H
