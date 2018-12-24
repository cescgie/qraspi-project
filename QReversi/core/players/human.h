#ifndef HUMAN_H
#define HUMAN_H

#include "core/players/virtualplayer.h"
#include "core/gameplay.h"

#include <QObject>

/// \brief Human player.
class Human : public VirtualPlayer
{
    Q_OBJECT

public:
    using VirtualPlayer::VirtualPlayer;

public slots:
    /// \brief Inform the human player.
    ///
    /// Note: Human players (this class) do not need to make sub-decisions in this method. The actual decision is decided by the real person. It only needs to follow the instructions of the real person.
    ///
    /// The #sigHelpMe() signal will be triggered when this slot is triggered.
    ///
    /// \param game No practical use.
    /// \param playerColor No practical use.
    void slotNextMove(const GamePlay::CheckerBoard &game, GamePlay::PlayerColor playerColor) override;
    /// \brief Tell this player where to go.
    /// \param position Chess position.
    void slotMoveTo(GamePlay::Position position);

signals:
    /// \brief Seek help signals.
    ///
    /// When it comes to human players, this class doesn't know how to play next game, let the outside world help it.
    void sigHelpMe();
};
#endif // HUMAN_H
