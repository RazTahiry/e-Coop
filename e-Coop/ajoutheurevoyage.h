#ifndef AJOUTHEUREVOYAGE_H
#define AJOUTHEUREVOYAGE_H

#include <QDialog>

namespace Ui {
class ajoutHeureVoyage;
}

class ajoutHeureVoyage : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutHeureVoyage(QWidget *parent = nullptr);
    ~ajoutHeureVoyage();

private:
    Ui::ajoutHeureVoyage *ui;
};

#endif // AJOUTHEUREVOYAGE_H
