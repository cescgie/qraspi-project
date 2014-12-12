#ifndef INFOVIEW_H
#define INFOVIEW_H

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

class InfoView : public QWidget
{
    Q_OBJECT
public:
    InfoView(QWidget *parent=0);
    ~InfoView();

    void connecting( game* );
    void writeSettings();
    void readSettings();
    Player* getPlayer(int);

    void setNameP1( QString name );
    void setNameP2( QString name );
    void setTypeP1( TypePlayer );
    void setTypeP2( TypePlayer );
    void setScoreP1( int score );
    void setScoreP2( int score );
private:

    Player **playerTable;

    QLabel  *namepar1, *namepar2,
            *levelpar1, *levelpar2,
            *nameP1, *nameP2,
            *typeP1, *typeP2,
            *line, *line2,
            *pawnBlack, *pawnWhite,
            *infosGame,
            *scoreP1Label, *scoreP2Label,
            *scoreP1, *scoreP2;

    QPainter *painterBlack,*painterWhite;

    QVBoxLayout *mainLayout;
    QGridLayout *topLayout;
    QHBoxLayout *toptopLayout, *centerLayout;

public slots:

    void updatingName(Player*);
    void updatingType(Player*);
    void setInfosGame(IdMsgInfos);
    void updatingScore();


};

#endif // INFOVIEW_H
