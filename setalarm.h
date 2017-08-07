#ifndef SETALARM_H
#define SETALARM_H

#include <QDialog>

namespace Ui {
class SetAlarm;
}

class SetAlarm : public QDialog
{
    Q_OBJECT

public:
    explicit SetAlarm(QWidget *parent = 0);
    ~SetAlarm();

private:
    Ui::SetAlarm *ui;
};

#endif // SETALARM_H
