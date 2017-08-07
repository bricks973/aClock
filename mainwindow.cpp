#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QtMath>
#include <string>
#include <QtMultimedia/QMediaPlayer>

QString wakeupTime = "00:11";
void setAlarm(bool onoff);
bool alarmIsOn = false;
int alarmTime; //how long the alarm has been going so we can slowly increase volume
int alarmVolume = 50; //start off at 0 then go to an ungodly volume

QMediaPlayer *player = new QMediaPlayer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QMainWindow::showFullScreen();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(myFunction()));
    timer->start(500);
    ui->lblNextAlarm->setText("Next Alarm: " + wakeupTime);
    player->setMedia(QUrl::fromLocalFile("/alarm.wav"));
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

    if (hours.length() < 2){hours = "  " + hours;}
    if (minutes.length() < 2){minutes = "0" + minutes;}
    ui->lblHours->setText(hours);
    ui->lblMinutes->setText(minutes);
    QString blinker = ui->lblBlinker->text();

//make blinker take half second on and half second off
    if(blinker == ":"){
        ui->lblBlinker->setText(" ");
    } else {
        ui->lblBlinker->setText(":");
        alarmIsOn = true;
        ui->lblNextAlarm->setText(QString::number(alarmVolume));

        if((alarmIsOn == true)&&(alarmVolume < 100)){
                alarmVolume = alarmVolume + 1;
                player->setVolume(alarmVolume);
                ui->lblNextAlarm->setText(QString::number(alarmVolume));
        }

    }

//declare seconds as float because the percentage calculation will need it
    float seconds = time.second();
    ui->lblSeconds->setText(time.toString("ss"));
    seconds = (seconds / 60) * 100;


    ui->pbarSeconds->setValue(seconds);
//Check if time = alarm time
    if(time_text.left(5) == wakeupTime){
        alarmIsOn = true;
        setAlarm(true);
        ui->lblNextAlarm->setText("Now!");
    }
}

void setAlarm(bool onoff){
    if(onoff){
            player->play();
            alarmIsOn = true;
    }else{
        player->stop();
        alarmIsOn = false;
    }

}
