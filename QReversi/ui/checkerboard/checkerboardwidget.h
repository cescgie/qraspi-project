#ifndef CHECKERBOARDWIDGET_H
#define CHECKERBOARDWIDGET_H

#include "core/gameplay.h"
#include "ui/checkerboard/boardgrid.h"

#include <QObject>
#include <QWidget>

#include <array>

/// \brief The checkerboard display controls.
///
/// This interface control is used to display the board
class CheckerBoardWidget : public QWidget
{
    Q_OBJECT

public:
    /// \brief Constructor
    explicit CheckerBoardWidget(QWidget *parent = nullptr);

    /// \brief Set the board.
    ///
    /// This function is used to set the board displayed on the board control.
    ///
    /// \param board CheckerBoard
    void setCheckerBoard(const GamePlay::CheckerBoard& board);

signals:
    /// \brief The next sub-signal is sent.
    /// \param position: Lower position
    void sigMoved(GamePlay::Position position);

private:
    std::array<std::array<BoardGrid*, GamePlay::kBoardColumns>, GamePlay::kBoardRows> m_grids;
};

#endif // CHECKERBOARDWIDGET_H
