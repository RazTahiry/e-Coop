#ifndef AJOUTTRAJET_H
#define AJOUTTRAJET_H

#include <QDialog>

namespace Ui {
class ajoutTrajet;
}

class ajoutTrajet : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutTrajet(QWidget *parent = nullptr);
    ~ajoutTrajet();

private:
    Ui::ajoutTrajet *ui;
};

#endif // AJOUTTRAJET_H
