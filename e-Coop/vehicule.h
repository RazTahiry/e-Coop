#ifndef VEHICULE_H
#define VEHICULE_H

#include "identificateur.h"
#include "trajets.h"

class Vehicule : public Identificateur, Trajets
{
    public:
        Vehicule();
        Vehicule(QString num_Matriculation, QString nom, QString contact, QString ref_trajet,
                 QString lieu_depart, QString destination, QString heure_depart, int nb_Place);

        void ajouter_vehicule(QString num_Matriculation, QString nom, QString contact, int nb_Place, QString ref_trajet);
        void modifier_vehicule(QString num_Matriculation, QString nom, QString contact, int nb_Place, QString ref_trajet);
        void supprimer_vehicule(QString num_Matriculation);

        void setHeure(QString num_Matriculation, QString heure_depart);

    private:
        QString _num_Matriculation;
        int _nb_Place;
};

#endif // VEHICULE_H
