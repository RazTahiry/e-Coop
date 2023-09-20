#include "ajoutheurevoyage.h"
#include "ui_ajoutheurevoyage.h"

ajoutHeureVoyage::ajoutHeureVoyage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutHeureVoyage)
{
    ui->setupUi(this);
}

ajoutHeureVoyage::~ajoutHeureVoyage()
{
    delete ui;
}
