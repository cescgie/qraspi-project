#ifndef _PREFERENCES_DIALOG_H
#define _PREFERENCES_DIALOG_H

#include <QDialog>
#include <QString>
#include "ui_preferencesdialog.h"

class PreferencesDialog : public QDialog, public Ui::PreferencesDialog
{
    Q_OBJECT

    public:

        PreferencesDialog(QWidget *parent = 0);

        void setNames(QString,QString);
        void setTypes(int, int);

};

#endif
