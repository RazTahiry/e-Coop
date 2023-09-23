#include "ajouttrajet.h"
#include "ui_ajouttrajet.h"

#include <QWidget>
#include <QtWidgets>
#include <QLayout>

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

void ajoutTrajet::on_pushButton_3_clicked()
{
    ajoutTrajet::close();
}

void ajoutTrajet::on_pushButton_clicked()
{
    QLineEdit* newLineEdit = new QLineEdit(this);
    newLineEdit->setFixedHeight(30);

    if(ui->arretContainer)
    {
        ui->arretContainer->layout()->addWidget(newLineEdit);
    }
    //ui->arretContainer->layout()->addWidget(newLineEdit);
}
