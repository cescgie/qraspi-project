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
};

#endif // GLVIEW_H
