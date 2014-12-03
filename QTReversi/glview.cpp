#include "glview.h"
#include <QtOpenGL>
#include "glu.h"

glView::glView(QWidget *parent)
        : QGLWidget(parent)
{
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

