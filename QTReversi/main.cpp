#include <QApplication>
#include <QtWidgets>
#include "graphics.h"
#include "game.h"
#include "ai.h"
#include "infoview.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

int main( int argc, char *argv[])
{
    srand( time(NULL) );

    QApplication app(argc, argv);

    game *ge = new game();
    graphics *grap = new graphics();
    ai *aieng = new ai();

    grap->initialization( ge );
    aieng->connecting( ge );

    grap->show();

    return app.exec();
}
