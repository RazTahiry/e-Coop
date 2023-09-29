#ifndef RESERVATION_H
#define RESERVATION_H

#include "identificateur.h"
#include "trajets.h"

class Reservation : public Identificateur, Trajets
{
    public:
        Reservation();
        Reservation(QString ref_place, QString nom, QString contact, QString cin,
                    int nb_place_reserve, QString membre_famille, QString contact_famille,
                    QString ref_trajet, QString lieu_depart, QString destination, QString heure_depart, bool isPaye);

        void reserver(QString ref_place, QString nom, QString contact, QString cin,
                      int nb_place_reserve, QString membre_famille, QString contact_famille,
                      QString ref_trajet, QString lieu_depart, QString destination, QString heure_depart, bool isPaye);

    private:
        QString _ref_place;
        QString _cin;
        int _nb_place_reserve;
        QString _membre_famille;
        QString _contact_famille;
        bool _isPaye;
};

#endif // RESERVATION_H
