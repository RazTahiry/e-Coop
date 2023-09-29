
#ifndef IDENTIFICATEUR_H
#define IDENTIFICATEUR_H

#include <QString>

class Identificateur
{
    public:
        Identificateur();
        Identificateur(QString nom, QString contact);

    protected:
        QString _nom;
        QString _contact;
};

#endif // IDENTIFICATEUR_H
