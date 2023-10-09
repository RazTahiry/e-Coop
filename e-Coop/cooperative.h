#ifndef COOPERATIVE_H
#define COOPERATIVE_H

#include "identificateur.h"

class Cooperative : public Identificateur
{
    public:
        Cooperative();
        Cooperative(QString ref_coop, QString nom, QString contact, QString contact1, QString contact2, QString address, QString datePremierVoyage);

        bool majCoop(QString nom, QString contact, QString contact1, QString contact2, QString address, QString datePremierVoyage);
        bool reinitialiser();

    private:
        QString _ref_coop;
        QString _address;
        QString _contact1;
        QString _contact2;
        QString _datePremierVoyage;
};

#endif // COOPERATIVE_H
