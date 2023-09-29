#ifndef COOPERATIVE_H
#define COOPERATIVE_H

#include "identificateur.h"

class Cooperative : public Identificateur
{
    public:
        Cooperative();
        Cooperative(QString ref_coop, QString nom, QString contact, QString address);

        void majCoop(QString nom, QString contact, QString address);
        void reinitialiser();

    private:
        QString _ref_coop;
        QString _address;
};

#endif // COOPERATIVE_H
