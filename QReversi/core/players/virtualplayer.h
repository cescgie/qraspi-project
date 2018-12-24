#ifndef REALPLAYER_H
#define REALPLAYER_H

#include "core/gameplay.h"

#include <QObject>

/// \brief Virtual player.
///
/// This class represents an abstract player that contains the basic operations of a player.
/// This is a pure virtual class, and the subclass must implement the decision to make a decision.
///
/// Example: A subclass of this class can be a human player, a computer player, or a player on the network.
class VirtualPlayer : public QObject
{
    Q_OBJECT

public:
    /// \brief Constructor.
    /// \param name first name.
    /// \param parent Parent control.
    explicit VirtualPlayer(QString name, QObject *parent = nullptr);

    /// \brief Get the name.
    /// \return The name of the player.
    QString getName() { return m_name; }

public slots:
    /// \brief Inform the player to play.
    ///
    /// Realize the chess decision here.
    ///
    /// \param game The board in the current game.
    /// \param playerColor The color of the player.
    virtual void slotNextMove(const GamePlay::CheckerBoard &game, GamePlay::PlayerColor playerColor) = 0;

signals:
    /// \brief Complete the sub-signal.
    /// \param position Lower position.
    void sigMoved(GamePlay::Position position);

private:
    QString m_name;
};

#endif // REALPLAYER_H
