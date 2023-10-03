#ifndef TRAJETS_H
#define TRAJETS_H

#include <QString>

class Trajets
{
    public:
        Trajets();
        Trajets(QString ref_trajet, QString lieu_depart, QString destination, QString heureMatin, QString heureSoir);

        void ajout_trajet(QString ref_trajet, QString lieu_depart, QString destination, QString heureMatin, QString heureSoir);
        void maj_trajet(QString ref_trajet, QString lieu_depart, QString destination, QString heureMatin, QString heureSoir);
        void supprimer_trajet(QString ref_trajet);

     protected:
        QString _ref_trajet;
        QString _lieu_depart;
        QString _destination;
        QString _heureMatin;
        QString _heureSoir;
};

#endif // TRAJETS_H
