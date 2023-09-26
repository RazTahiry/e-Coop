#include "passager.h"

Passager::Passager()
{
    this->_cin = "";
    this->_famille = "";
    this->_contact_famille = "";
    this->_lieu_depart = "";
    this->_lieu_arrive = "";
    this->_heure_depart = "";
    this->_frais = false;
}

Passager::Passager(QString nom, QString contact, QString cin, QString famille,
                   QString contact_famille, QString lieu_depart, QString lieu_arrive,
                   QString heure_depart, bool frais):
    Identificateur(nom, contact)
{
    this->_cin = cin;
    this->_famille = famille;
    this->_contact_famille = contact_famille;
    this->_lieu_depart = lieu_depart;
    this->_lieu_arrive = lieu_arrive;
    this->_heure_depart = heure_depart;
    this->_frais = frais;
}

QString Passager::get_cin()
{
    return _cin;
}

QString Passager::get_famille()
{
    return _famille;
}

QString Passager::get_contact_famille()
{
    return _contact_famille;
}

QString Passager::get_lieu_depart()
{
    return _lieu_depart;
}

QString Passager::get_heure_depart()
{
    return _heure_depart;
}

bool Passager::isPaye()
{
    return _frais;
}

void Passager::set_cin(QString cin)
{
    this->_cin = cin;
}

void Passager::set_famille(QString famille)
{
    this->_famille = famille;
}

void Passager::set_contact_famille(QString contact_famille)
{
    this->_contact_famille = contact_famille;
}

void Passager::set_lieu_depart(QString lieu_depart)
{
    this->_lieu_depart = lieu_depart;
}

void Passager::set_lieu_arrive(QString lieu_arrive)
{
    this->_lieu_arrive = lieu_arrive;
}

void Passager::set_heure_depart(QString heure_depart)
{
    this->_heure_depart = heure_depart;
}

void Passager::set_isPaye(bool frais)
{
    this->_frais = frais;
}

void Passager::reserver(QString nom, QString contact, QString cin, QString famille,
                        QString contact_famille, QString lieu_depart, QString lieu_arrive,
                        QString heure_depart, bool frais)
{
    Passager::set_Nom(nom);
    Passager::set_Contact(contact);
    Passager::set_cin(cin);
    Passager::set_famille(famille);
    Passager::set_contact_famille(contact_famille);
    Passager::set_lieu_depart(lieu_depart);
    Passager::set_lieu_arrive(lieu_arrive);
    Passager::set_heure_depart(heure_depart);
    Passager::set_isPaye(frais);
}
