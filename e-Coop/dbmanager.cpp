#include "dbmanager.h"
#include <QDebug>

DbManager::DbManager()
{
}

DbManager::DbManager(const QString& path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if(!db.open())
    {
        qDebug() << "Database connexion failed...";
    }
    else
    {
        qDebug() << "Database connexion succeeded...";
    }
}

bool DbManager::isOpen() const
{
    return db.isOpen();
}

DbManager::~DbManager()
{
    if(db.isOpen())
    {
        db.close();
        qDebug() << "Database closed.";
    }
}
