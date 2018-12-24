#ifndef AI_H
#define AI_H

#include "core/players/virtualplayer.h"
#include "core/gameplay.h"

#include <QObject>

/// \brief Computer player.
class Ai : public VirtualPlayer
{
    Q_OBJECT

public:
    using VirtualPlayer::VirtualPlayer;

    /// \brief Setting up the game
    void setGame(GamePlay* game);

public slots:
    /// \brief Inform the computer player.
    ///
    /// The computer player here makes the decision to take the next move.
    ///
    /// \param game The board in the current game.
    /// \param playerColor The color of the player.
    void slotNextMove(const GamePlay::CheckerBoard &game, GamePlay::PlayerColor playerColor) override;

private:
    GamePlay* m_game;
};

inline void Ai::setGame(GamePlay *game)
{
    m_game = game;
}

#endif // AI_H
