#include <QtGui>

#include "preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    connect( ok_pushButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( cancel_pushButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

void PreferencesDialog::setNames(QString name_p1, QString name_p2)
{
    if( name_p1.isEmpty() )
        name_p1 = QString(tr("Player 1"));
    if( name_p2.isEmpty() )
        name_p2 = QString(tr("Player 2"));

    lineEdit_name_p1->setText(name_p1);
    lineEdit_name_p2->setText(name_p2);
}

void PreferencesDialog::setTypes(int type_p1, int type_p2)
{
    comboBox_type_p1->setCurrentIndex(type_p1);
    comboBox_type_p2->setCurrentIndex(type_p2);
}
