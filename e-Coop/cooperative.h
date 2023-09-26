#ifndef COOPERATIVE_H
#define COOPERATIVE_H

#include "identificateur.h"

class Cooperative : public Identificateur
{
    public:
        Cooperative();
        Cooperative(QString nom, QString contact, QString ref_coop, QString address);

        QString get_ref_coop();
        QString get_address();

        void set_ref_cop(QString ref_coop);
        void set_address(QString address);

        void reinitialiser();

    private:
        QString _ref_coop;
        QString _address;
};

#endif // COOPERATIVE_H
