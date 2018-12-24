#ifndef PIECEGIRD_H
#define PIECEGIRD_H

#include "core/gameplay.h"

#include <QPushButton>

/// \brief Checkerboard grid.
///
/// Each checkerboard has its position and attribution (black, white or unknown).
/// Click on a checkerboard grid to place it in the position it is in.
class BoardGrid : public QPushButton
{
    Q_OBJECT

public:
    static const size_t kGridSize = 64;
    static const size_t kStoneRadius = 24;

    /// \brief Constructor.
    /// \param position The position of the grid.
    /// \param stoneColor The color of the pieces on the grid.
    /// \param parent Parent control
    BoardGrid(GamePlay::Position position, GamePlay::PlayerColor stoneColor = GamePlay::PlayerColor::Unknown, QWidget *parent = nullptr);
    ~BoardGrid() override;

    /// \brief Change the color of the pieces on the grid.
    /// \param stoneColor Chess color.
    void setStoneColor(GamePlay::PlayerColor stoneColor);

public slots:
    /// \brief Click on the event that the grid is triggered.
    void slotOnClicked();

signals:
    /// \brief The next sub-signal is sent.
    /// \param position Lower position
    void sigMoved(GamePlay::Position position);

protected:
    void paintEvent(QPaintEvent *event) override;
    bool event(QEvent *event) override;

private:
    GamePlay::Position m_position;
    GamePlay::PlayerColor m_playerColor;
    bool m_hovered = false;
};

#endif // PIECEGIRD_H
