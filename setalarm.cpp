#include "setalarm.h"
#include "ui_setalarm.h"

SetAlarm::SetAlarm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetAlarm)
{
    ui->setupUi(this);
}

SetAlarm::~SetAlarm()
{
    delete ui;
}
