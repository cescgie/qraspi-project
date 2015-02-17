#ifndef _INFOWINDOW_H
#define _INFOWINDOW_H

#include <QtWidgets>
#include <define.h>

class game;
class Player;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QTextEdit;
class QSizePolicy;

class infoView : public QWidget
{
        Q_OBJECT

        public:
                //Konstruktor
                infoView(QWidget *parent=0);
                ~infoView();
                void connecting( game* );
                void writeSettings();
                void readSettings();
                Player* getPlayer(int);

                void setColorP1( ColorPawn );
                void setColorP2( ColorPawn );
                void setNameP1( QString name );
                void setNameP2( QString name );
                void setTypeP1( TypePlayer );
                void setTypeP2( TypePlayer );
                void setScoreP1( int score );
                void setScoreP2( int score );
                void setMovesP1( int num );
                void setMovesP2( int num );

        private:
                Player **playerTable;
                QLabel *colorP1, *colorP2,
                        *namepar1, *namepar2,
                        *levelpar1, *levelpar2,
                        *scoreP1Label, *scoreP2Label,
                        *movesP1Label, *movesP2Label,
                        *nameP1, *nameP2,
                        *scoreP1, *scoreP2,
                        *movesP1, *movesP2,
                        *typeP1, *typeP2,
                        *infosGame,
                        *line, *line2,
                        *dot1, *dot2, *dot3, *dot4, *dot5,
                        *pawnBlack, *pawnWhite;

                QPainter *hit,*hit2;
                QVBoxLayout *mainLayout;
                QGridLayout *topLayout;
                QHBoxLayout *toptopLayout;

                void initComponent();

        public slots:
                void updatingName(Player*);
                void updatingType(Player*);
                void updatingColor(Player*);
                void updatingScore();
                void updatingMoves();
                void setInfosGame(IdMsgInfos);
};

#endif
