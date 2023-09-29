#ifndef VEHICULE_H
#define VEHICULE_H

#include "identificateur.h"
#include "trajets.h"

class Vehicule : public Identificateur, Trajets
{
    public:
        Vehicule();
        Vehicule(QString num_Matriculation, QString nom, QString contact, int nb_Place);

        void ajouter_vehicule(QString num_Matriculation, QString nom, QString contact, int nb_Place);
        void modifier_vehicule(QString nom, QString contact, QString num_Matriculation, int nb_Place);
        void supprimer_vehicule(QString num_Matriculation);

    private:
        QString _num_Matriculation;
        int _nb_Place;
};

#endif // VEHICULE_H
