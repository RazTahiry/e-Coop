#ifndef AJOUTJOURSVOYAGE_H
#define AJOUTJOURSVOYAGE_H

#include <QDialog>

namespace Ui {
class ajoutJoursVoyage;
}

class ajoutJoursVoyage : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutJoursVoyage(QWidget *parent = nullptr);
    ~ajoutJoursVoyage();

private:
    Ui::ajoutJoursVoyage *ui;
};

#endif // AJOUTJOURSVOYAGE_H
