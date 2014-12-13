#include "glview.h"
#include <QtOpenGL>
#include "GL/glu.h"
#include "glview.h"
#include "board.h"

glView::glView(QWidget *parent)
        : QGLWidget(parent)
{
    clearColor = Qt::darkGray;
    setAnimated( false );
    setMoveAsked(false);
    angle = 180;
    board = NULL;
    animationSetting = true;
    regularMovesSetting = true;

    timer = new QTimer(this);
    connect(timer, SIGNAL( timeout() ), this, SLOT( updateScene() ) );

}

glView::~glView()
{
}

QSize glView::minimumSizeHint() const
{
        return QSize(600,600);
}

QSize glView::sizeHint() const
{
        return QSize(500,500);
}

void glView::updateGL()
{
}

void glView::updateScene()
{
    if( animationSetting == false )
        {
            board->clearAnimation();
        }

        if( board->getAnimated() && getAnimated()==false )
        {
            timer->start( 10 );
            setAnimated( true );
        }
        if( getAnimated() )
            {
            angle -= AngleSpeedAnimation;
                if( angle <= 0 )
                {
                    angle = 180;
                    setAnimated( false );
                    board->clearAnimation();
                    timer->stop();
                    emit animationDone();
                }
            }
        repaint();

            if( animationSetting == false )
            {
                emit animationDone();
            }
}

void glView::initializeGL()
{
    qglClearColor(clearColor);
    glEnable(GL_DEPTH_TEST);
    loadTextures();
    boardLayout = makeBoard();
}

void glView::resizeGL(int width, int height)
{

    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 100.0, 0.0, 0, 100.0);  //orthogonal-Ansicht
    glMatrixMode(GL_MODELVIEW);
}

void glView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0,0.0,-50.0);
    glCallList(boardLayout);

    drawPawnsLayout();
}

void glView::pawnDrawing(GLUquadricObj *quadric)
{
    glPushMatrix();
        qglColor(Qt::black);
        gluCylinder(quadric,4.5,4.5,1,20,20);
        glTranslatef(0.0,0.0,1.0f);
        gluDisk(quadric,0,4.5,20,20);
        glPopMatrix();
        qglColor(Qt::white);
        glTranslatef(0.0,0.0,-1.0);
        gluCylinder(quadric,4.5,4.5,1,20,20);
        gluDisk(quadric,0,4.5,20,20);
        glPopMatrix();

}

void glView::drawPawnsLayout()
{
    GLUquadricObj *quadric = gluNewQuadric();
        gluQuadricDrawStyle(quadric, GLU_FILL);

        for( int y=0 ; y<8 ; y++ ){
            for( int x=0 ; x<8 ; x++ ){

                switch( board->getTypeSquareBoard(x,y) )
                {
                    case Occupied:
                        glPushMatrix();
                        glTranslatef(WidthBorderText + x*WidthSquareText + WidthRadiusPawn, WidthBorderText + y*WidthSquareText + WidthRadiusPawn, 5.0f);
                        if( board->getColorPawnBoard(x,y) == White )
                        {
                            glRotatef(180,0.0f,1.0f,0.0f);
                        }
                        if( board->getAnimatedSquare(x, y) )
                        {
                            glRotatef(angle,0.0f,1.0f,0.0f);  //Rotation du pion pour l'animation
                        }
                        pawnDrawing(quadric);

                        break;
                    case RegularMove:
                        if( getRegularMovesSetting() )
                        {
                            glPushMatrix();
                            glTranslatef(WidthBorderText + x*WidthSquareText + WidthRadiusPawn, WidthBorderText + y*WidthSquareText + WidthRadiusPawn, 5.0f);
                            regularMoveDrawing(quadric);
                         }
                          break;
                     case Empty:
                          break;
                     default:
                          break;
                                }
                            }
                        }
          gluDeleteQuadric(quadric);
}

void glView::regularMoveDrawing(GLUquadricObj *quadric)
{
        qglColor(Qt::darkGreen);
        gluDisk(quadric,0,1.0,20,20);
        glPopMatrix();
}

void glView::mousePressEvent(QMouseEvent *event)
{

}
void glView::mouseReleaseEvent(QMouseEvent *event)
{
    if( getMoveAsked() )
        {
            int squareX, squareY,
                clicX = event->x(), clicY = event->y(),
                widthWidget = width(), heightWidget = height();

            int widthBoard = widthWidget;
            if( heightWidget < widthWidget )
            {
                widthBoard = heightWidget;
            }
            int widthBorder = widthBoard / ( 2.0 + (8.0 * WidthSquareText / WidthBorderText) );
                    int widthSquare = (widthBoard - (2*widthBorder)) / 8.0;

                    if( widthWidget > heightWidget )
                    {
                        squareX = ( clicX - ( (widthWidget-heightWidget)/2.0 ) - widthBorder ) / ( widthSquare );
                        squareY = ( clicY - widthBorder ) / ( widthSquare );
                    }
                    else if( widthWidget < heightWidget )
                            {
                                squareX = ( clicX - widthBorder ) / ( widthSquare );
                                squareY = ( clicY - ((heightWidget-widthWidget)/2.0) - widthBorder ) / (widthSquare);
                            }
                            else
                            {
                                squareX = ( clicX - widthBorder ) / widthSquare;
                                squareY = ( clicY - widthBorder ) / widthSquare;
                            }
                    if( squareX >= 0 && squareY >= 0 && squareX<8 && squareY<8 )
                            {
                                setMoveAsked(false);
                                emit boardHasClicked(squareX,squareY);
                            }
                        }
}

void glView::loadTextures()
{
        QImage t, b;
        //batik.bmp||wood.bmp||sand.bmp||Board.bmp||Field.bmp
        b.load( "Stone.bmp" );
        t = QGLWidget::convertToGLFormat( b );
        glGenTextures( 1, &textures[0] );
        glBindTexture( GL_TEXTURE_2D, textures[0] );
        glTexImage2D( GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits() );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}

GLuint glView::makeBoard()
{
        GLuint list = glGenLists(1);
        glNewList(list, GL_COMPILE);

        glEnable(GL_TEXTURE_2D);

        qglColor(Qt::white);

        glBindTexture(GL_TEXTURE_2D, textures[0]);

        glBegin(GL_QUADS);
                        glTexCoord2d(0,1);  glVertex3f( 0.0f,0.0f, 0.0f);
                        glTexCoord2d(0,0);  glVertex3f( 0.0f, 100.0f, 0.0f);
                        glTexCoord2d(1,0);  glVertex3f( 100.0f, 100.0f, 0.0f);
                        glTexCoord2d(1,1);  glVertex3f( 100.0f,0.0f, 0.0f);
        glEnd();

        glDisable(GL_TEXTURE_2D);

        glEndList();

        return list;
}
void glView::setRegularMovesSetting( bool b)
{
        regularMovesSetting = b;
        updateScene();
}

bool glView::getRegularMovesSetting()
{
        return regularMovesSetting;
}

void glView::setAnimationSetting( bool b)
{
    animationSetting = b;
}

bool glView::getAnimationSetting()
{
    return animationSetting;
}


void glView::setAnimated( bool b)
{
    animated =b;
}

bool glView::getAnimated()
{
    return animated;
}

void glView::setMoveAsked(bool b)
{
    moveAsked = b;
}

bool glView::getMoveAsked()
{
    return moveAsked;
}

void glView::askingMoveReceived()
{
    setMoveAsked(true);
}

void glView::setBoard(Board *b)
{
    board = b;
}

void glView::connecting( game *ge )
{
    connect( this, SIGNAL( boardHasClicked(int,int) ), ge, SLOT( recupMove(int,int) ) );
    connect( ge, SIGNAL( askingLocalMove() ), this, SLOT( askingMoveReceived() ) );
    connect( this, SIGNAL( animationDone() ), ge, SLOT( nextTurn() ) );
    connect( ge, SIGNAL( boardModified() ), this, SLOT( updateScene() ) );

    setBoard( ge->getBoard() );
}
