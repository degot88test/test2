#include "mainwindow.h"
#include <iostream>
#include <windows.h>
#include <QtGui>
#include <QtCore>

MainClass::MainClass(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{

    label = new QLabel("Time:",this) ;

    Reset = new QPushButton();
    Uni = new QPushButton();
    Inc = new QPushButton();
    Dec = new QPushButton();

    QGridLayout* pgrdLayout = new QGridLayout;

    QPixmap reset("reset.png");
    QPixmap pix("play.png");
    QPixmap inc("inc.png");
    QPixmap dec("dec.png");

    pgrdLayout->addWidget(label, 1, 2);
    pgrdLayout->addWidget(Reset, 0, 1);
    pgrdLayout->addWidget(Uni, 0, 0);
    pgrdLayout->addWidget(Inc, 1, 1);
    pgrdLayout->addWidget(Dec, 1, 0);
    pgrdLayout->addWidget(&progress_bar,0,2);

    Reset->setIcon(reset);
    Reset->setIconSize(reset.size());

    Uni->setIcon(pix);
    Uni->setIconSize(pix.size());

    Inc->setIcon(inc);
    Inc->setIconSize(inc.size());

    Dec->setIcon(dec);
    Dec->setIconSize(dec.size());

    QObject::connect(Uni, SIGNAL(clicked()), SLOT(slotUni()));
    QObject::connect(Reset, SIGNAL(clicked()), SLOT(slotReset()));
    QObject::connect(Inc,SIGNAL(clicked()),SLOT(slotInc()));
    QObject::connect(Dec,SIGNAL(clicked()),SLOT(slotDec()));

    setLayout(pgrdLayout);

    progress_bar.setMinimumWidth(100);
    progress_bar.setAlignment(Qt::AlignCenter);
    QObject::connect(&timer, SIGNAL(timeout()), SLOT(updTime()));
    QObject::connect(&timer, SIGNAL(timeout()), SLOT(updPb()));
    QObject::connect(&timer, SIGNAL(timeout()), SLOT(update()));

    cond = COND_PAUSE;

    N = 600;

    timer.setInterval(N);

    total_time = temp_time = 0;

}

MainClass::~MainClass(){}

void MainClass::slotStart( void )
{

    qDebug() << 1;
    QPixmap pix("pause.png");
    Uni->setIcon(pix);
    Uni->setIconSize(pix.size());
    timer.start();
}


void MainClass::slotStop()
{
    QPixmap pix1("play.png");
    Uni->setIcon(pix1);
    Uni->setIconSize(pix1.size());
    timer.stop();

    temp_time = 0;

}

void MainClass::slotReset()
{
    progress_bar.reset();
    progress_bar.setValue(0);
    timer.stop();

    temp_time = 0;

}

void MainClass::slotUni()
{
    if (cond == COND_PAUSE) {

        this->slotStart();

        cond = COND_GO;
    } else {
        this->slotStop();

        cond = COND_PAUSE;
    }
}

void MainClass::slotInc()
{
    N/=2;
    timer.setInterval(N);
}

void MainClass::slotDec()
{
    N*=2;
    timer.setInterval(N);
}


void MainClass::slotTxt()
{
    QObject::connect(&timer, SIGNAL(timeout()),this, SLOT(update()));
}


void MainClass::updTime()
{
    total_time += (N/1000.);
    temp_time += (N/1000.);

    QString ts;
    ts.sprintf("Total %.2lf Temp %.2lf", total_time, temp_time);
    label->setText(ts);
    qDebug() << ts;

}

void MainClass::updPb()
{
    if( progress_bar.value() >= progress_bar.maximum() ); // ??? wtf
    progress_bar.setValue(progress_bar.value()+1);

}


