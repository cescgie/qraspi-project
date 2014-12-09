#include "graphics.h"
#include "game.h"
#include <QApplication>
#include <QtWidgets>

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

    grap->initialization( ge );
    grap->show();

    return a.exec();
}
