#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();  // Mainwindowu tam ekran açar


    // sure
    QTimer *saniye=new QTimer(this);
    saniye->start(1000);
    connect(saniye,&QTimer::timeout,this,&MainWindow::sureGuncelle);


    // belirli bir surede yeni balon olusturuyor
    QTimer *timerBalon=new QTimer(this);
    timerBalon->start(750);
    connect(timerBalon,&QTimer::timeout,this,&MainWindow::rastgeleBalonOlustur);


    // belirli bir surede yerdegistir fonksiyonunu cagiriyor
    QTimer *timer=new QTimer(this);
    timer->start(8);
    connect(timer,&QTimer::timeout,this,&MainWindow::balonKaydir);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rastgeleBalonOlustur()
{
    int randX, randY;
    dialogWidth = QMainWindow::width() - 50;  // Mainwindow genisliginden 50px cikariyoruz tam sifir konumunda balon olusmasin diye
    dialogHeight = QMainWindow::height();  // Mainwindow yuksekligi. Balon bu siniri gecerse kacirilmis sayilir.

    randX = rand() % ((dialogWidth + 1) - 50) + 50;  // balonlar soldan ve sagdan 50px bosluk birakacak ana pencerenin icinde
    randY = 80;

    Balon *balon = new Balon(this);
    balon->setGeometry(randX, randY, 50, 50);

    balonlar.push_back(balon);
    balon->setIcon(QIcon(":/balonlar/images/" + QString::number(rand() % 7) + ".jpg"));
    balon->setIconSize(QSize(50, 50));
    balon->show();
}


void MainWindow::sureGuncelle()
{
    int sure = ui->lbl_Sure->text().toInt() + 1;
    ui->lbl_Sure->setText(QString::number(sure));
}


void MainWindow::vurulanBalonSayGuncelle()
{
    int sayi=balonlar.size(), vurulanBalonSay=0;
    for (int i=0; i<sayi; ++i){
        if(balonlar[i]->patladimi){
            vurulanBalonSay++;
        }
    }
    ui->lbl_vurulanBalonSay->setText(QString::number(vurulanBalonSay));
}


void MainWindow::kacanBalonSayGuncelle()
{
    kacanBalonSay = ui->lbl_kacanBalonSay->text().toInt() + 1;
    ui->lbl_kacanBalonSay->setText(QString::number(kacanBalonSay));
}


void MainWindow::balonKaydir()
{
    int sayi=balonlar.size();
    for (int i=0; i<sayi; ++i){
        if(!balonlar[i]->patladimi && !balonlar[i]->kactimi){  // Balon patlatilmadiysa ve oyun alanindaysa
            // Balon oyun alaninin icindeyse
            if(balonlar[i]->y() <= dialogHeight){
                balonlar[i]->move(balonlar[i]->x(), balonlar[i]->y()+1);  // Balon y ekseninde 1px asagi kayar

                // balona oyun alanindayken tiklanirsa
                connect(balonlar[i],&QPushButton::clicked, [this,i]{
                    balonlar[i]->balonPatlat();
                    vurulanBalonSayGuncelle();
                    QTimer::singleShot(500,[this, i]{
                        balonlar[i]->hide();
                    });

                });

            // Balon oyun alaninindan ciktiysa
            }else{
                balonlar[i]->balonKacti();
                kacanBalonSayGuncelle();
                balonlar[i]->hide();
            }
        }
    }
}
