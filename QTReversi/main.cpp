#include "graphics.h"
#include "game.h"
#include <QApplication>
#include <QtWidgets>
#include "ai.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    srand( time(NULL) );

    QApplication a(argc, argv);

    game *ge = new game();
    graphics *grap= new graphics();
    ai *aipt = new ai();

    grap->initialization( ge );
    aipt->connecting(ge);

    grap->show();

    return a.exec();
}
