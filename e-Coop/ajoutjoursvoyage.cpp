#include "ajoutjoursvoyage.h"
#include "ui_ajoutjoursvoyage.h"

ajoutJoursVoyage::ajoutJoursVoyage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutJoursVoyage)
{
    ui->setupUi(this);
}

ajoutJoursVoyage::~ajoutJoursVoyage()
{
    delete ui;
}
