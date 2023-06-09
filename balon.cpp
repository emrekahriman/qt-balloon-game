#include "balon.h"

Balon::Balon(QWidget *parrent):QPushButton(parrent)
{
    patladimi = false;
    kactimi = false;
    connect(this,&QPushButton::clicked,this,&Balon::balonPatlat);
}


void Balon::balonPatlat()
{
    if(!patladimi){
        patladimi = true;
        QPushButton::setIcon(QIcon(":/patlama/images/patlama.jpg"));
        QPushButton::setIconSize(QSize(50, 50));
    }

}


void Balon::balonKacti()
{
    if(!kactimi){
        kactimi = true;
   }
}

