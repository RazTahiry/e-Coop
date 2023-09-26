#ifndef PASSAGER_H
#define PASSAGER_H

#include "identificateur.h"

class Passager : public Identificateur
{
    public:
        Passager();
        Passager(QString nom, QString contact, QString cin, QString famille,
                 QString contact_famille, QString lieu_depart, QString lieu_arrive,
                 QString heure_depart, bool frais);

        QString get_cin();
        QString get_famille();
        QString get_contact_famille();
        QString get_lieu_depart();
        QString get_lieu_arrive();
        QString get_heure_depart();
        bool isPaye();

        void set_cin(QString cin);
        void set_famille(QString famille);
        void set_contact_famille(QString contact_famille);
        void set_lieu_depart(QString lieu_depart);
        void set_lieu_arrive(QString lieu_arrive);
        void set_heure_depart(QString heure_depart);
        void set_isPaye(bool frais);

        void reserver(QString nom, QString contact, QString cin, QString famille,
                      QString contact_famille, QString lieu_depart, QString lieu_arrive,
                      QString heure_depart, bool frais);

    private:
        QString _cin;
        QString _famille;
        QString _contact_famille;
        QString _lieu_depart;
        QString _lieu_arrive;
        QString _heure_depart;
        bool _frais;
};

#endif // PASSAGER_H
