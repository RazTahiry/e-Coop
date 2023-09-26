#include "vehicule.h"

Vehicule::Vehicule()
{
    this->_num_Matriculation = "";
    this->_nb_Place = 0;
}

Vehicule::Vehicule(QString nom, QString contact,
                   QString num_Matriculation, int nb_Place):
    Identificateur(nom, contact)
{
    this->_num_Matriculation = num_Matriculation;
    this->_nb_Place = nb_Place;
}

QString Vehicule::get_num_Matriculation()
{
    return _num_Matriculation;
}

int Vehicule::get_nb_Place()
{
    return _nb_Place;
}

void Vehicule::set_num_Matriculation(QString num_Matriculation)
{
    this->_num_Matriculation = num_Matriculation;
}

void Vehicule::set_nb_Place(int nb_Place)
{
    this->_nb_Place = nb_Place;
}

void Vehicule::ajouter_vehicule(QString nom, QString contact, QString num_Matriculation, int nb_Place)
{
    Vehicule::set_Nom(nom);
    Vehicule::set_Contact(contact);
    Vehicule::set_num_Matriculation(num_Matriculation);
    Vehicule::set_nb_Place(nb_Place);
}

void Vehicule::modifier_vehicule(QString nom, QString contact, QString num_Matriculation, int nb_Place)
{
    Vehicule::set_Nom(nom);
    Vehicule::set_Contact(contact);
    Vehicule::set_num_Matriculation(num_Matriculation);
    Vehicule::set_nb_Place(nb_Place);
}

void Vehicule::supprimer_vehicule()
{

}
