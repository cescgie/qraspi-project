#include "glview.h"
#include <QtOpenGL>
#include "glu.h"

glView::glView(QWidget *parent)
        : QGLWidget(parent)
{
    clearColor = Qt::darkGray;
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
