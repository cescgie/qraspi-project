#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QMainWindow>
#include "glview.h"

class QAction;
class QLabel;
class QWidget;

#include <iostream>
#include <cstring>
using namespace std;

class graphics : public QMainWindow
{
    Q_OBJECT

public:
    graphics(QWidget *parent = 0);
    ~graphics();

protected:
        void closeEvent(QCloseEvent *event);

private slots:
    void newGame();

private:
     void createActions();
     void createMenus();
     void createStatusBar();

     QWidget *centralWindow;
     glView *scene;

     QMenu *fileMenu;

     QAction *newAction;
     QAction *exitAction;

     QLabel *statusBarLabel;

};

#endif // GRAPHICS_H
