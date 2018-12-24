#ifndef BOARDLAYOUT_H
#define BOARDLAYOUT_H

#include <QObject>
#include <QGridLayout>

/// \brief Checkerboard layout.
///
/// This class controls the layout of the board display controls.
class BoardLayout : public QGridLayout
{
    Q_OBJECT

public:
    explicit BoardLayout(QWidget *parent);
    ~BoardLayout();
};

#endif // BOARDLAYOUT_H
