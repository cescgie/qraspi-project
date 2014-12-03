#ifndef GLVIEW_H
#define GLVIEW_H

#include <QGLWidget>
#include "glu.h"

class QTimer;

class glView : public QGLWidget
{
public:
    glView(QWidget *parent=0);
    ~glView();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void updateGL();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    QColor clearColor;

    GLuint textures[1];
    GLuint makeBoard();
    GLuint boardLayout;

    void loadTextures();
};

#endif // GLVIEW_H
