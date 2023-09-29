#ifndef TRAJETS_H
#define TRAJETS_H

#include <QString>

class Trajets
{
    public:
        Trajets();
        Trajets(QString ref_trajet, QString lieu_depart, QString destination, QString heure_depart);

        void ajout_trajet(QString ref_trajet, QString lieu_depart, QString destination, QString heure_depart);
        void maj_trajet(QString ref_trajet, QString lieu_depart, QString destination, QString heure_depart);
        void supprimer_trajet(QString ref_trajet);

private:
        QString _ref_trajet;
        QString _lieu_depart;
        QString _destination;
        QString _heure_depart;
};

#endif // TRAJETS_H
