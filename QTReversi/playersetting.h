#ifndef PLAYERSETTING_H
#define PLAYERSETTING_H

#include <QDialog>
#include <QString>
#include "ui_playersetting.h"

class PlayerSetting : public QDialog, public Ui::PlayerSetting
{
        Q_OBJECT

        public:
                PlayerSetting(QWidget *parent = 0);
                void setNames(QString,QString);
                void setTypes(int, int);
};
#endif // PLAYERSETTING_H
