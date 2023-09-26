#ifndef IDENTIFICATEUR_H
#define IDENTIFICATEUR_H

#include <QString>

class Identificateur
{
    public:
        Identificateur();
        Identificateur(QString nom, QString contact);

        QString get_Nom();
        QString get_Contact();

        void set_Nom(QString nom);
        void set_Contact(QString contact);

    protected:
        QString _nom;
        QString _contact;
};

#endif // IDENTIFICATEUR_H
