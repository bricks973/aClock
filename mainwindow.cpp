#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QtMath>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QMainWindow::showFullScreen();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(myFunction()));
    timer->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myFunction()
{
//get the current time
    QTime time = QTime::currentTime();
    QString AMPM = "";
//format it to hours minutes and seconds, then seperate them
    QString time_text = time.toString("hh:mm:ss");
    QString minutes = time.toString("mm");

//check hours.  if above 12 then its pm, else its am
    int h = time.hour();
    QString hours = "";
    if (h >= 12){
        AMPM = "PM";
        if (h == 12){hours = "12";} else {h = h-12; hours = QString::number(h);}
    } else {
        AMPM = "AM";
        if (h == 0){hours = "12";} else {hours = h;}
    }

    ui->lblAMPM->setText(AMPM);


    ui->lblHours->setText(hours);
    ui->lblMinutes->setText(minutes);
    QString blinker = ui->lblBlinker->text();

//make blinker take half second on and half second off
    if(blinker == ":"){
        ui->lblBlinker->setText(" ");
    } else {
        ui->lblBlinker->setText(":");
    }

//declare seconds as float because the percentage calculation will need it
    float seconds = time.second();
    ui->lblSeconds->setText(time.toString("ss"));
    seconds = (seconds / 60) * 100;


    ui->pbarSeconds->setValue(seconds);

   //ui->lblSeconds->setText(Sec);
}
