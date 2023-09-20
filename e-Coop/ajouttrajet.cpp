#include "ajouttrajet.h"
#include "ui_ajouttrajet.h"

ajoutTrajet::ajoutTrajet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutTrajet)
{
    ui->setupUi(this);
}

ajoutTrajet::~ajoutTrajet()
{
    delete ui;
}
