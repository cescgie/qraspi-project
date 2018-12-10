/********************************************************************************
** Form generated from reading UI file 'playersetting.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERSETTING_H
#define UI_PLAYERSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerSetting
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_p1;
    QGridLayout *gridLayout1;
    QLabel *label_name_p1;
    QLineEdit *lineEdit_name_p1;
    QSpacerItem *spacerItem;
    QLabel *label_type_p1;
    QComboBox *comboBox_type_p1;
    QVBoxLayout *vboxLayout;
    QPushButton *ok_pushButton;
    QPushButton *cancel_pushButton;
    QGroupBox *groupBox_p2;
    QGridLayout *gridLayout2;
    QLabel *label_name_p2;
    QLineEdit *lineEdit_name_p2;
    QSpacerItem *spacerItem1;
    QLabel *label_type_p2;
    QComboBox *comboBox_type_p2;

    void setupUi(QWidget *PlayerSetting)
    {
        if (PlayerSetting->objectName().isEmpty())
            PlayerSetting->setObjectName(QStringLiteral("PlayerSetting"));
        PlayerSetting->resize(404, 217);
        gridLayout = new QGridLayout(PlayerSetting);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_p1 = new QGroupBox(PlayerSetting);
        groupBox_p1->setObjectName(QStringLiteral("groupBox_p1"));
        gridLayout1 = new QGridLayout(groupBox_p1);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        label_name_p1 = new QLabel(groupBox_p1);
        label_name_p1->setObjectName(QStringLiteral("label_name_p1"));

        gridLayout1->addWidget(label_name_p1, 0, 0, 1, 1);

        lineEdit_name_p1 = new QLineEdit(groupBox_p1);
        lineEdit_name_p1->setObjectName(QStringLiteral("lineEdit_name_p1"));

        gridLayout1->addWidget(lineEdit_name_p1, 0, 1, 1, 1);

        spacerItem = new QSpacerItem(31, 41, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout1->addItem(spacerItem, 0, 2, 2, 1);

        label_type_p1 = new QLabel(groupBox_p1);
        label_type_p1->setObjectName(QStringLiteral("label_type_p1"));

        gridLayout1->addWidget(label_type_p1, 1, 0, 1, 1);

        comboBox_type_p1 = new QComboBox(groupBox_p1);
        comboBox_type_p1->addItem(QString());
        comboBox_type_p1->addItem(QString());
        comboBox_type_p1->addItem(QString());
        comboBox_type_p1->addItem(QString());
        comboBox_type_p1->setObjectName(QStringLiteral("comboBox_type_p1"));

        gridLayout1->addWidget(comboBox_type_p1, 1, 1, 1, 1);


        gridLayout->addWidget(groupBox_p1, 0, 0, 1, 1);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        ok_pushButton = new QPushButton(PlayerSetting);
        ok_pushButton->setObjectName(QStringLiteral("ok_pushButton"));
        ok_pushButton->setEnabled(true);
        ok_pushButton->setCheckable(false);
        ok_pushButton->setChecked(false);

        vboxLayout->addWidget(ok_pushButton);

        cancel_pushButton = new QPushButton(PlayerSetting);
        cancel_pushButton->setObjectName(QStringLiteral("cancel_pushButton"));
        cancel_pushButton->setCheckable(false);

        vboxLayout->addWidget(cancel_pushButton);


        gridLayout->addLayout(vboxLayout, 0, 1, 1, 1);

        groupBox_p2 = new QGroupBox(PlayerSetting);
        groupBox_p2->setObjectName(QStringLiteral("groupBox_p2"));
        gridLayout2 = new QGridLayout(groupBox_p2);
        gridLayout2->setObjectName(QStringLiteral("gridLayout2"));
        label_name_p2 = new QLabel(groupBox_p2);
        label_name_p2->setObjectName(QStringLiteral("label_name_p2"));

        gridLayout2->addWidget(label_name_p2, 0, 0, 1, 1);

        lineEdit_name_p2 = new QLineEdit(groupBox_p2);
        lineEdit_name_p2->setObjectName(QStringLiteral("lineEdit_name_p2"));

        gridLayout2->addWidget(lineEdit_name_p2, 0, 1, 1, 1);

        spacerItem1 = new QSpacerItem(40, 51, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem1, 0, 2, 2, 1);

        label_type_p2 = new QLabel(groupBox_p2);
        label_type_p2->setObjectName(QStringLiteral("label_type_p2"));

        gridLayout2->addWidget(label_type_p2, 1, 0, 1, 1);

        comboBox_type_p2 = new QComboBox(groupBox_p2);
        comboBox_type_p2->addItem(QString());
        comboBox_type_p2->addItem(QString());
        comboBox_type_p2->addItem(QString());
        comboBox_type_p2->addItem(QString());
        comboBox_type_p2->setObjectName(QStringLiteral("comboBox_type_p2"));

        gridLayout2->addWidget(comboBox_type_p2, 1, 1, 1, 1);


        gridLayout->addWidget(groupBox_p2, 1, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        label_name_p1->setBuddy(lineEdit_name_p1);
        label_type_p1->setBuddy(comboBox_type_p1);
        label_name_p2->setBuddy(lineEdit_name_p2);
        label_type_p2->setBuddy(comboBox_type_p2);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lineEdit_name_p1, comboBox_type_p1);
        QWidget::setTabOrder(comboBox_type_p1, lineEdit_name_p2);
        QWidget::setTabOrder(lineEdit_name_p2, comboBox_type_p2);
        QWidget::setTabOrder(comboBox_type_p2, ok_pushButton);
        QWidget::setTabOrder(ok_pushButton, cancel_pushButton);

        retranslateUi(PlayerSetting);

        ok_pushButton->setDefault(true);


        QMetaObject::connectSlotsByName(PlayerSetting);
    } // setupUi

    void retranslateUi(QWidget *PlayerSetting)
    {
        PlayerSetting->setWindowTitle(QApplication::translate("PlayerSetting", "Preferences", nullptr));
        groupBox_p1->setTitle(QApplication::translate("PlayerSetting", "Player 1", nullptr));
        label_name_p1->setText(QApplication::translate("PlayerSetting", "&Name :", nullptr));
        label_type_p1->setText(QApplication::translate("PlayerSetting", "&Type :", nullptr));
        comboBox_type_p1->setItemText(0, QApplication::translate("PlayerSetting", "Human", nullptr));
        comboBox_type_p1->setItemText(1, QApplication::translate("PlayerSetting", "Computer ( Beginner )", nullptr));
        comboBox_type_p1->setItemText(2, QApplication::translate("PlayerSetting", "Computer ( Amateur )", nullptr));
        comboBox_type_p1->setItemText(3, QApplication::translate("PlayerSetting", "Computer (  Expert   )", nullptr));

        ok_pushButton->setText(QApplication::translate("PlayerSetting", "&Ok", nullptr));
        cancel_pushButton->setText(QApplication::translate("PlayerSetting", "&Cancel", nullptr));
        groupBox_p2->setTitle(QApplication::translate("PlayerSetting", "Player 2", nullptr));
        label_name_p2->setText(QApplication::translate("PlayerSetting", "&Name :", nullptr));
        label_type_p2->setText(QApplication::translate("PlayerSetting", "&Type :", nullptr));
        comboBox_type_p2->setItemText(0, QApplication::translate("PlayerSetting", "Human", nullptr));
        comboBox_type_p2->setItemText(1, QApplication::translate("PlayerSetting", "Computer ( Beginner )", nullptr));
        comboBox_type_p2->setItemText(2, QApplication::translate("PlayerSetting", "Computer ( Amateur )", nullptr));
        comboBox_type_p2->setItemText(3, QApplication::translate("PlayerSetting", "Computer ( Expert )", nullptr));

    } // retranslateUi

};

namespace Ui {
    class PlayerSetting: public Ui_PlayerSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERSETTING_H
