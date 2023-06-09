#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <qrandom.h>
#include <QPushButton>
#include "balon.h"
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void rastgeleBalonOlustur();
    void balonKaydir();
    void sureGuncelle();
    void vurulanBalonSayGuncelle();
    void kacanBalonSayGuncelle();


private:
    Ui::MainWindow *ui;
    QList<Balon*> balonlar;
    int dialogWidth;
    int dialogHeight;
    int vurulanBalonSay;
    int kacanBalonSay;
};
#endif // MAINWINDOW_H
