#include "graphics.h"
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

    graphics w;
    w.show();

    return a.exec();
}
