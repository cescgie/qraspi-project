#ifndef _LISTMOVES_H
#define _LISTMOVES_H

#include <QtWidgets>
#include <define.h>

class game;
class Player;
class QLabel;
class QVBoxLayout;
class QTextEdit;
class QSizePolicy;

class ListMoves : public QWidget
{
        Q_OBJECT

        public:
                //Konstruktor
                ListMoves(QWidget *parent=0);
                ~ListMoves();
                void connecting( game* );
                void writeSettings();
                void readSettings();
                Player* getPlayer(int);

        private:

                Player **playerTable;
                QLabel  *movesListLabel;
                QTextEdit *listMoves;
                QGridLayout *mainLayout;

                void initComponent();
        public slots:
                void setListMoves( QString);
};

#endif
