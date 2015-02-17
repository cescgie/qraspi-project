#ifndef _GLWINDOW_H
#define _GLWINDOW_H

#include <QGLWidget>
#include "game.h"
#include "GL/glu.h"
#include <GL/glu.h>

class QTimer;
class board;

class glView : public QGLWidget
{
    Q_OBJECT

    public:
        glView(QWidget *parent=0);
                ~glView();
        QSize minimumSizeHint() const;
        QSize sizeHint() const;
        void setAnimationSetting( bool );
        bool getAnimationSetting();
        void setRegularMovesSetting( bool );
        bool getRegularMovesSetting();
        void setLastMoveSetting( bool );
        bool getLastMoveSetting();
        void connecting( game* );
        void setMoveAsked(bool);
        void initializeGL();

    public slots:
        void updateGL();
        void updateScene();

        void askingMoveReceived();


    protected:

        void resizeGL(int width, int height);
        void paintGL();
        void pawnDrawing(GLUquadricObj *);
        void regularMoveDrawing(GLUquadricObj *);
        void lastMoveDrawing(GLUquadricObj *);
        void drawPawnsLayout();
        void mousePressEvent(QMouseEvent *);
        void mouseReleaseEvent(QMouseEvent *);

    private:
        Board *board;
        GLuint makeBoard();
        void loadTextures();
        GLuint textures[1];
        GLuint boardLayout;
        QColor clearColor;

        bool animationSetting;
        bool regularMovesSetting;
        bool lastMoveSetting;
        bool animated;
        void setAnimated( bool );
        bool getAnimated();
        int angle;
        QTimer *timer;
        bool moveAsked;
        bool getMoveAsked();
        void setBoard(Board*);

    signals:
        void boardHasClicked(int,int);
        void animationDone();
};

#endif
