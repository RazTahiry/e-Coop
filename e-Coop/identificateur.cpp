#include "identificateur.h"

Identificateur::Identificateur():
    _nom(""), _contact(""){
}

Identificateur::Identificateur(QString nom, QString contact):
    _nom(nom), _contact(contact){
}

QString Identificateur::get_Nom()
{
    return _nom;
}

QString Identificateur::get_Contact()
{
    return _contact;
}

void Identificateur::set_Nom(QString nom)
{
    _nom = nom;
}

void Identificateur::set_Contact(QString contact)
{
    _contact = contact;
}

