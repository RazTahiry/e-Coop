#include "ajoutvehicule.h"
#include "ui_ajoutvehicule.h"

ajoutVehicule::ajoutVehicule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutVehicule)
{
    ui->setupUi(this);
}

ajoutVehicule::~ajoutVehicule()
{
    delete ui;
}

void ajoutVehicule::on_annulerBtn_clicked()
{
    ajoutVehicule::close();
}
