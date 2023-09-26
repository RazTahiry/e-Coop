#ifndef VEHICULE_H
#define VEHICULE_H

#include "identificateur.h"

class Vehicule : public Identificateur
{
    public:
        Vehicule();
        Vehicule(QString nom, QString contact, QString num_Matriculation, int nb_Place);

        QString get_num_Matriculation();
        int get_nb_Place();

        void set_num_Matriculation(QString num_Matriculation);
        void set_nb_Place(int nb_Place);

        void ajouter_vehicule(QString nom, QString contact, QString num_Matriculation, int nb_Place);
        void modifier_vehicule(QString nom, QString contact, QString num_Matriculation, int nb_Place);
        void supprimer_vehicule();

    private:
        QString _num_Matriculation;
        int _nb_Place;
};

#endif // VEHICULE_H
