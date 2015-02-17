#include <QtGui>
#include <QtOpenGL>
#include "GL/glu.h"

#include "glview.h"
#include "board.h"

glView::glView(QWidget *parent)
        : QGLWidget(parent)
{
        clearColor = Qt::black;
        setAnimated( false );
        setMoveAsked(false);
        angle = 180;
        board = NULL;
        animationSetting = true;
        regularMovesSetting = true;
        lastMoveSetting = true;
        timer = new QTimer(this);
        connect(timer, SIGNAL( timeout() ), this, SLOT( updateScene() ) );
}

glView::~glView()
{
}

//Mindestgröße Fenster
QSize glView::minimumSizeHint() const
{
        return QSize(600,600);
}

//Größe beim Start
QSize glView::sizeHint() const
{
        return QSize(500,500);
}




void glView::updateGL()
{
}

void glView::updateScene()
{
//      cout << "\tEntre ds \"glView::updateScene()\"" << endl;

        if( animationSetting == false )
        {
                board->clearAnimation();
        }

        if( board->getAnimated() && getAnimated()==false )
        {
                timer->start( 10 );
                setAnimated( true );
        }


        if( getAnimated() )  //Wenn die Szene animiert
        {
        angle -= AngleSpeedAnimation;  //Verschiebung des Drehwinkels der Animation
                if( angle <= 0 )  //Animation abgeschlossen
                {
                        angle = 180;
                        setAnimated( false );
                        board->clearAnimation();
                        timer->stop();
                        emit animationDone();
                }
        }

        repaint();  //Zeichnet das Widget

        if( animationSetting == false )
        {
                emit animationDone();
        }
}


//Die Initialisierung der OpenGL-Maschine
void glView::initializeGL()
{
        //Einstellen der Hintergrundfarbe
        qglClearColor(clearColor);

        //Aktivieren des Z-Puffers
        glEnable(GL_DEPTH_TEST);

        //Laedt Texturen
        loadTextures();

        //kreieren der Spielflaeche
        boardLayout = makeBoard();
}

void glView::resizeGL(int width, int height)
{
    //Definieren der Ansichtsfenster
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    //Definieren der Projektionsmatrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 100.0, 0.0, 0, 100.0);  //orthogonal-Ansicht
    glMatrixMode(GL_MODELVIEW);
}

void glView::paintGL()
{
    //Füllen des Fensters mit Hintergrundfarbe
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Das Löschen des Bildpuffers (COLOR_BUFFER) und des Tiefenpuffers (DEPTH_BUFFER)
    glLoadIdentity();
    //Camera
    glTranslatef(0.0,0.0,-50.0);

    //zeichnet Spielflaeche
    glCallList(boardLayout);

    //zeichnet Spielsteine
    drawPawnsLayout();
}

    //Zeichnet eine Figur auf dem Bildschirm
    //Schwarze Sichtseite
void glView::pawnDrawing(GLUquadricObj *quadric)
{
        glPushMatrix();  //sichern der Matrix
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

void glView::regularMoveDrawing(GLUquadricObj *quadric)
{
        qglColor(Qt::darkGreen);
        gluDisk(quadric,0,1.0,20,20);
        glPopMatrix();
}

void glView::lastMoveDrawing(GLUquadricObj *quadric)
{
        glTranslatef(0.0,0.0,2.0);
        qglColor(Qt::red);
        gluDisk(quadric,0,1.0,20,20);
        glPopMatrix();
}

//Alle Spielfiguren auf dem Bildschirm
void glView::drawPawnsLayout()
{
        GLUquadricObj *quadric = gluNewQuadric();  //erstellt ein Quadrat
        gluQuadricDrawStyle(quadric, GLU_FILL);  //Zeichenmodus

        //Weg auf Spielflaeche
        for( int y=0 ; y<8 ; y++ ){
                for( int x=0 ; x<8 ; x++ ){

                        switch( board->getTypeSquareBoard(x,y) )
                        {
                                case Occupied:  //Box wird besetzt durch Spielfigur
                                        glPushMatrix();
                                        glTranslatef(WidthBorderText + x*WidthSquareText + WidthRadiusPawn, WidthBorderText + y*WidthSquareText + WidthRadiusPawn, 5.0f);
                                        if( board->getColorPawnBoard(x,y) == White )  //Wenn es ein weißer Stein ist, muss er zurückkehren
                                        {
                                                glRotatef(180,0.0f,1.0f,0.0f);
                                        }
                                        if( board->getAnimatedSquare(x, y) )
                                        {  //Wenn es ein Stein ist
                                                glRotatef(angle,0.0f,1.0f,0.0f);  //Drehung des Steines durch Animation
                                        }
                                        pawnDrawing(quadric);
                                        if( getLastMoveSetting() && board->getLastMoveSquare(x,y) )
                                        {  //Wenn das Kontrollkästchen der zuletzt gespielten
                                                //Letzten Zug anzeigen
                                                glPushMatrix();
                                                glTranslatef(WidthBorderText + x*WidthSquareText + WidthRadiusPawn, WidthBorderText + y*WidthSquareText + WidthRadiusPawn, 5.0f);
                                                lastMoveDrawing(quadric);
                                        }
                                        break;
                                case RegularMove:  //Zug legal
                                        if( getRegularMovesSetting() )
                                        {
                                                glPushMatrix();
                                                glTranslatef(WidthBorderText + x*WidthSquareText + WidthRadiusPawn, WidthBorderText + y*WidthSquareText + WidthRadiusPawn, 5.0f);
                                                regularMoveDrawing(quadric);
                                        }
                                        break;
                                case Empty:  //Leerer Kasten
                                        break;
                                default:  //Fall unmöglich, wenn ohne Fehler...
                                        break;
                        }
                }
        }
        gluDeleteQuadric(quadric);
}


void glView::mousePressEvent( QMouseEvent *event )
{
}

void glView::mouseReleaseEvent( QMouseEvent * event )
{
//      unsetCursor();
//      setCursor(Qt::ArrowCursor);
//      setCursor(Qt::PointingHandCursor);

//      cout << "Entre ds \"glView::mouseReleaseEvent()\"" << endl;

        if( getMoveAsked() )  //Wenn ein Umzug durch die Game-Engine angefordert wird
        {
                int squareX, squareY,
                        clicX = event->x(), clicY = event->y(),
                        widthWidget = width(), heightWidget = height();

                //Berechnen der Breite der Spielflaeche ( = min(widthWidget,heightWidget) )
                int widthBoard = widthWidget;
                if( heightWidget < widthWidget )
                {
                        widthBoard = heightWidget;
                }
                //Breite des Rahmens in der Widget-Anzeigepixel
                int widthBorder = widthBoard / ( 2.0 + (8.0 * WidthSquareText / WidthBorderText) );
                //Breite einer Box in der Widget-Anzeigepixel
                int widthSquare = (widthBoard - (2*widthBorder)) / 8.0;

                //Breiter als Hoehe
                if( widthWidget > heightWidget )
                {
                        squareX = ( clicX - ( (widthWidget-heightWidget)/2.0 ) - widthBorder ) / ( widthSquare );
                        squareY = ( clicY - widthBorder ) / ( widthSquare );
                }

                //Hoeher als Breite
                else if( widthWidget < heightWidget )
                {
                        squareX = ( clicX - widthBorder ) / ( widthSquare );
                        squareY = ( clicY - ((heightWidget-widthWidget)/2.0) - widthBorder ) / (widthSquare);
                }
                //Breite = Höhe
                else
                {
                        squareX = ( clicX - widthBorder ) / widthSquare;
                        squareY = ( clicY - widthBorder ) / widthSquare;
                }

//              squareX--;
//              squareY--;

                if( squareX >= 0 && squareY >= 0 && squareX<8 && squareY<8 )
                {
                        setMoveAsked(false);  //Demande du coup réalisé dc askingMove=false
//                      cout << "Emission de \"glView::boardHasClicked(int,int)\"" << endl;
                        emit boardHasClicked(squareX,squareY);
                }
        }
}


GLuint glView::makeBoard()
{
        GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);

        //Aktivieren 2D Texturierung
        glEnable(GL_TEXTURE_2D);

                //Auswahl der Farbe "Weiß", um sich nicht einmischen Texturierung
                qglColor(Qt::white);

                //Auswahl der Textur anwenden
                glBindTexture(GL_TEXTURE_2D, textures[0]);

                //Zeichnung der Spielflaeche
                glBegin(GL_QUADS);
                        glTexCoord2d(0,1);  glVertex3f( 0.0f,0.0f, 0.0f);
                        glTexCoord2d(0,0);  glVertex3f( 0.0f, 100.0f, 0.0f);
                        glTexCoord2d(1,0);  glVertex3f( 100.0f, 100.0f, 0.0f);
                        glTexCoord2d(1,1);  glVertex3f( 100.0f,0.0f, 0.0f);
                glEnd();

                //Deaktivieren der 2D Texturierung
                glDisable(GL_TEXTURE_2D);

        glEndList();

        return list;
}

void glView::loadTextures()
{
        QImage t, b;
        //batik.bmp||wood.bmp||sand.bmp||Board.bmp||Field.bmp
        b.load( ":/images/Stone.bmp" );
        t = QGLWidget::convertToGLFormat( b );
        glGenTextures( 1, &textures[0] );
        glBindTexture( GL_TEXTURE_2D, textures[0] );
        glTexImage2D( GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits() );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        timer->start();
}


void glView::setAnimationSetting( bool b)
{
        animationSetting = b;
}

bool glView::getAnimationSetting()
{
        return animationSetting;
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

void glView::setLastMoveSetting( bool b)
{
        lastMoveSetting = b;
        updateScene();
}

bool glView::getLastMoveSetting()
{
        return lastMoveSetting;
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
//      cout << "Entre ds \"glView::setMoveAsked(" << b << ")\"" << endl;
        moveAsked = b;
//      cout << "\tglView::moveAsked = " << moveAsked << endl;
}

bool glView::getMoveAsked()
{
//      cout << "Entre ds \"glView::getMoveAsked()\"" << endl;
//      cout << "\tglView::moveAsked = " << moveAsked << endl;
        return moveAsked;
}

void glView::askingMoveReceived()
{
//      cout << "Entre ds \"glView::askingMoveReceived()\"" << endl;
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
