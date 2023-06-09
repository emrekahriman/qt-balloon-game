#ifndef BALON_H
#define BALON_H


#include <QPushButton>


class Balon : public QPushButton
{
    Q_OBJECT
public:
    Balon(QWidget *parrent=0);
    bool patladimi;
    bool kactimi;

public slots:
    void balonPatlat();
    void balonKacti();
};

#endif // BALON_H
