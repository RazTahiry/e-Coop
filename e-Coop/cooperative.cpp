#include "cooperative.h"

Cooperative::Cooperative()
{
    this->_ref_coop = "";
    this->_address = "";
}

Cooperative::Cooperative(QString nom, QString contact,
                         QString ref_coop, QString address):
    Identificateur(nom, contact)
{
    this->_ref_coop = ref_coop;
    this->_address = address;
}

QString Cooperative::get_ref_coop()
{
    return _ref_coop;
}

QString Cooperative::get_address()
{
    return _address;
}

void Cooperative::set_ref_cop(QString ref_coop)
{
    this->_ref_coop = ref_coop;
}

void Cooperative::set_address(QString address)
{
    this->_address = address;
}

void Cooperative::reinitialiser()
{
    this->_nom = "";
    this->_contact = "";
    this->_ref_coop = "";
    this->_address = "";
}
