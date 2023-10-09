#ifndef VEHICULE_H
#define VEHICULE_H

#include "identificateur.h"
#include "trajets.h"

class Vehicule : public Identificateur, Trajets
{
    public:
        Vehicule();
        Vehicule(QString num_Matriculation, QString nom, QString contact, QString ref_trajet,
                 QString lieu_depart, QString destination, QString heureMatin, QString heureSoir, int nb_Place, int decalage);

        bool ajouter_vehicule(QString num_Matriculation, QString nom, QString contact, int nb_Place, QString ref_trajet);
        bool modifier_vehicule(QString num_Matriculation, QString nom, QString contact, int nb_Place, QString ref_trajet);
        bool supprimer_vehicule(QString num_Matriculation);

    private:
        QString _num_Matriculation;
        int _nb_Place;
};

#endif // VEHICULE_H
