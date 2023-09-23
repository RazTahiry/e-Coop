#ifndef AJOUTVEHICULE_H
#define AJOUTVEHICULE_H

#include <QDialog>

namespace Ui {
class ajoutVehicule;
}

class ajoutVehicule : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutVehicule(QWidget *parent = nullptr);
    ~ajoutVehicule();

private slots:
    void on_annulerBtn_clicked();

private:
    Ui::ajoutVehicule *ui;
};

#endif // AJOUTVEHICULE_H
