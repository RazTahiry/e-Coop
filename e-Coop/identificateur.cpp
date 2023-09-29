#include "identificateur.h"

Identificateur::Identificateur():
    _nom(""), _contact("")
{
}

Identificateur::Identificateur(QString nom, QString contact):
    _nom(nom), _contact(contact)
{
}


