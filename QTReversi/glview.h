#ifndef GLVIEW_H
#define GLVIEW_H

#include <QGLWidget>
#include "game.h"
#include "GL/glu.h"

class QTimer;
class Board;

class glView : public QGLWidget
{
    Q_OBJECT

    public:
        //Constructor
        glView(QWidget *parent=0);
        ~glView();

        QSize minimumSizeHint() const;
        QSize sizeHint() const;


        void setAnimationSetting( bool );
        bool getAnimationSetting();
        void setRegularMovesSetting( bool );
        bool getRegularMovesSetting();

        void connecting( game* );

        void setMoveAsked(bool);

    public slots:
        void updateGL();
        void updateScene();

        void askingMoveReceived();


    protected:
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void pawnDrawing(GLUquadricObj *);
        void drawPawnsLayout();
        void regularMoveDrawing(GLUquadricObj *);


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
