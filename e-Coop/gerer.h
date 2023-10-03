#ifndef GERER_H
#define GERER_H

#include "dbmanager.h"
#include "reservation.h"
#include "trajets.h"
#include "vehicule.h"

#include <QString>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMap>
#include <QList>
#include <QTime>

class Gerer
{
    //Q_OBJECT

    public:
        Gerer();
        Gerer(QString num_Matriculation, QString ref_trajet);
        void gere();
        void setHeure(const QTime& heure);

        bool compareVehicles(const Gerer &v1, const Gerer &v2);


    private:
        QString _id;
        QString _trj;
        QTime _heure;
        QTime _heure1;
};



#endif // GERER_H
