#include "gestiontrajet.h"
#include "dbmanager.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>
#include <QStringList>
#include <QTime>
#include <ctime>
#include <QDate>

gestionTrajet::gestionTrajet()
{
}

void gestionTrajet::gerer()
{
    DbManager db(pathToDB);

    //---- Lister les vehicules avec leur refTrajet
    QHash<QString, QStringList> vehicules;

    QSqlQuery query("SELECT numMAT, refTrajet FROM VEHICULE");

    while (query.next())
    {
        QString numMAT = query.value(0).toString();
        QString refTrajet = query.value(1).toString();

        if(!vehicules.contains(refTrajet))
        {
            vehicules.insert(refTrajet, QStringList());
        }
        vehicules[refTrajet].append(numMAT);
    }

    //---------- Affichage véhicule par trajet --------------------------------------
    QHash<QString, QStringList>::const_iterator i = vehicules.constBegin();
    while (i != vehicules.constEnd())
    {
        QString key = i.key();
        QStringList values = i.value();

        qDebug() << "RefTrajet:" << key;

        foreach (QString value, values)
        {
            qDebug() << "  Véhicules:" << value;
        }
        ++i;
    }
    //--------------------------------------------------------------------------------

    //---- Récuperation décalage
    QHash<QString, QList<int>> decalage;
    QSqlQuery selectDecalage("SELECT refTrajet, decalageVoyage FROM TRAJET");
    while (selectDecalage.next())
    {
        QString refTrajet = selectDecalage.value(0).toString();
        int decalageVoyage = selectDecalage.value(1).toInt();

        if(!decalage.contains(refTrajet))
        {
            decalage.insert(refTrajet, QList<int>());
        }
        decalage[refTrajet].append(decalageVoyage);
    }

    //----------------------- Affichage décalage --------------------------------------
    QHash<QString, QList<int>>::const_iterator j = decalage.constBegin();
    while (j != decalage.constEnd())
    {
        QString refTrajet = j.key();
        QList<int> decal = j.value();

        qDebug() << "RefTrajet:" << refTrajet;

        foreach (int value, decal)
        {
            qDebug() << "  Décalage:" << value;
        }
        ++j;
    }
    //----------------------------------------------------------------------------------

    QSqlQuery selectDate("SELECT datePremierVoyage FROM COOPERATIVE");
    while (selectDate.next())
    {
        //---- Récuperation heure par chaque trajet
        QMap<QString, QSqlRecord> heureMap;
        QSqlQuery selectHeure("SELECT refTrajet, heureMatin, heureSoir FROM TRAJET");
        while (selectHeure.next())
        {
            QString ref = selectHeure.value(0).toString();

            QSqlRecord heure(selectHeure.record());
            QVariant heureM = selectHeure.value(1);
            QVariant heureS = selectHeure.value(2);

            heure.setValue("heureMatin", heureM);
            heure.setValue("heureSoir", heureS);

            heureMap.insert(ref, heure);
        }

        //---- Affichage heure par trajet ------------------------------------------
        QMap<QString, QSqlRecord>::const_iterator k = heureMap.constBegin();

        while (k != heureMap.constEnd())
        {
            QString cle = k.key();
            QSqlRecord hour = heureMap.value(cle);

            qDebug() << "Reftrajet: " << cle;
            qDebug() << "   Heure Matin: " << hour.value("heureMatin").toString();
            qDebug() << "   Heure Soir: " << hour.value("heureSoir").toString();

            ++k;
        }
        //-----------------------------------------------------------------------------

        //---- Récuperation lieu de départ et destination
        QMap<QString, QPair<QString,QString>> trajet;
        QSqlQuery selectTrajet("SELECT refTrajet, lieuDepart, destination FROM TRAJET");
        while (selectTrajet.next())
        {
            QString idTrajet = selectTrajet.value(0).toString();
            QString depart = selectTrajet.value(1).toString();
            QString destination = selectTrajet.value(2).toString();

            QPair<QString, QString> trajetPair(depart, destination);

            trajet.insert(idTrajet,trajetPair);
        }

        //-------- Affichage allé et retour ------------------------------------------
        QMap<QString, QPair<QString,QString>>::const_iterator l = trajet.constBegin();
        while (l != trajet.constEnd())
        {
            QString cles = l.key();
            QPair<QString, QString> pairs = trajet.value(cles);

            qDebug() << "***Trajet: " << cles;
            qDebug() << "       allé et retour: " << pairs;

            ++l;
        }
        //----------------------------------------------------------------------------

        QString datePremierVoyage = selectDate.value(0).toString();
        QDate dateFinal(2023, 10, 10);

        for(QDate premierVoyage = QDate::fromString(datePremierVoyage, "dd/MM/yyyy"); premierVoyage <= dateFinal; premierVoyage = premierVoyage.addDays(2))
        {
           //---- Ajout heure Matin et heure Soir pour chaque vehicule
           QHash<QString, QStringList>::const_iterator i = vehicules.constBegin();
           while (i != vehicules.constEnd())
           {
               QString key = i.key();
               QStringList values = i.value();

               QSqlRecord heureValue = heureMap.value(key);

               foreach(QString voiture, values)
               {
                   //---- Ajout numMat, refTrajet et date dans la Table GESTION
                   QSqlQuery addToGetsion;
                   addToGetsion.prepare("INSERT INTO GESTION (numMAT, refTrajet, dateVoyage) VALUES (:numMAT, :refTrajet, :dateVoyage)");
                   addToGetsion.bindValue(":numMAT", voiture);
                   addToGetsion.bindValue(":refTrajet", key);
                   addToGetsion.bindValue(":dateVoyage", premierVoyage);
                   addToGetsion.exec();

                   //---- Ajout heure pour chaque vehicule dans la Table GESTION
                   QString heure_matin = heureValue.value("heureMatin").toString();
                   QString heure_soir = heureValue.value("heureSoir").toString();

                   //---- Les vehicules avec l'indice paire prennent l'heure matin et celles sont impaire prennent l'heure soir
                   if((values.indexOf(voiture) + 1) % 2 == 0)
                   {
                       QSqlQuery addHour1;
                       addHour1.prepare("UPDATE GESTION SET heure = :heureMatin WHERE numMAT = :numMAT");
                       addHour1.bindValue(":heureMatin", heure_matin);
                       addHour1.bindValue(":numMAT", voiture);
                       addHour1.exec();
                   }
                   else
                   {
                       QSqlQuery addHour2;
                       addHour2.prepare("UPDATE GESTION SET heure = :heureSoir WHERE numMAT = :numMAT");
                       addHour2.bindValue(":heureSoir", heure_soir);
                       addHour2.bindValue(":numMAT", voiture);
                       addHour2.exec();
                   }
              }

              //---- Ajout lieu de depart et destination pour chaque vehicule
              QPair<QString, QString> trajetPair = trajet.value(key);
              QString depart = trajetPair.first;
              QString dest = trajetPair.second;

              qSwap(depart, dest); // Lieu de départ et destination swappé

              if(values.size() <= 2)
              {
                  for(int i = 0; i < values.size(); i++)
                  {
                       QSqlQuery addDestiny;
                       addDestiny.prepare("UPDATE GESTION SET lieuDepart = :dep, destination = :dest WHERE refTrajet = :reference AND numMAT = :numMAT");
                       addDestiny.bindValue(":dep", depart);
                       addDestiny.bindValue(":dest", dest);
                       addDestiny.bindValue(":reference", key);
                       addDestiny.bindValue(":numMAT", values[i]);
                       addDestiny.exec();
                  }
              }
              else
              {
                   for(int i = 0; i < values.size(); i += 2)
                   {
                       if((i + 1) < values.size())
                       {
                           QSqlQuery addDestiny1;
                           addDestiny1.prepare("UPDATE GESTION SET lieuDepart = :dep, destination = :dest WHERE refTrajet = :reference AND numMAT = :numMAT");
                           addDestiny1.bindValue(":dep", depart);
                           addDestiny1.bindValue(":dest", dest);
                           addDestiny1.bindValue(":reference", key);
                           addDestiny1.bindValue(":numMAT", values[i]);
                           addDestiny1.exec();

                           qSwap(depart, dest); // Lieu de départ et destination swappé

                           QSqlQuery addDestiny2;
                           addDestiny2.prepare("UPDATE GESTION SET lieuDepart = :dep, destination = :dest WHERE refTrajet = :reference AND numMAT = :numMAT");
                           addDestiny2.bindValue(":dep", depart);
                           addDestiny2.bindValue(":dest", dest);
                           addDestiny2.bindValue(":reference", key);
                           addDestiny2.bindValue(":numMAT", values[i + 1]);
                           addDestiny2.exec();
                       }
                   }
              }
              ++i;
          }
          qDebug() << premierVoyage;
       }
   }
}
