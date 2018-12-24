#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>

#include "core/battle.h"

namespace Ui {
class NewGameDialog;
}

/// \brief New game dialog.
class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameDialog(QWidget *parent = nullptr);
    ~NewGameDialog();

    /// \brief Set up the battle.
    void setBattle(Battle* battle) { m_battle = battle; }

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewGameDialog *ui;

    Battle* m_battle;
};

#endif // NEWGAMEDIALOG_H
