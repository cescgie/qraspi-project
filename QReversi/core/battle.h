#ifndef ROUND_H
#define ROUND_H

#include "core/gameplay.h"
#include "core/players/virtualplayer.h"

#include <QObject>

/// \brief The battle class represents a game.
///
/// There are two players in Black and White in a match. Players can have different player types.
///
/// Remember, in every new battle, it is always Black's first mover.
class Battle : public QObject
{
    Q_OBJECT

public:
    /// \brief The next child color.
    using PlayerColor = GamePlay::PlayerColor;
    /// \brief Player type.
    enum PlayerType {
        Human,
        Ai
    };

    /// \brief Constructor.
    explicit Battle(QObject *parent = nullptr);
    ~Battle();

    /// \brief Whether it is in the middle of the battle.
    /// \return If you are fighting, then true。
    bool isBattleRunning();
    /// \brief The current sub-party.
    /// \return The current sub-party.
    PlayerColor currentPlayerColor();
    /// \brief Get the players in the game.
    /// \param playerColor Player color,
    ///        Need to be #GamePlay::Black or #GamePlay::White 。
    /// \return Players corresponding to the next child \p playerColor. If there is no match, it is nullptr.
    VirtualPlayer *getPlayer(PlayerColor playerColor);

    /// \brief Start the game.
    /// \param blackPlayerType Black player type.
    /// \param whitePlayerType White player type.
    /// \param blackPlayerName Black player name.
    /// \param whitePlayerName White's player name.
    void startNewBattle(PlayerType blackPlayerType, PlayerType whitePlayerType,
                        QString blackPlayerName = "Black Player", QString whitePlayerName = "White Player");
    /// \brief End the battle.
    ///
    /// This function is used to end the battle midway and will not emit a sigBattleEnded() signal.
    void endBattle();

public slots:
    /// \brief Human players.
    ///
    /// Accept a request from a human being.
    ///
    /// Note: A valid child will only occur when it is the turn of a human player.
    ///
    /// \param position Lower position.
    void slotHumanMove(GamePlay::Position position);

signals:
    /// \brief Status change signal.
    ///
    /// This signal is sent when any state changes occur. Such as: start, end, change under the child.
    void sigChanged();
    /// \brief The battle begins with a signal.
    void sigBattleStarted();
    /// \brief The end of the game signal.
    ///
    /// This signal is issued during the normal end of the battle.
    ///
    /// \param winner Winner, the draw is Unknown.
    void sigBattleEnded(PlayerColor winner);
    /// \brief The next player changes the signal.
    /// \param playerColor The current sub-party.
    void sigPlayerChanged(PlayerColor playerColor);
    /// \brief The board changes the signal.
    ///
    /// This signal is sent when the board changes. This signal is sent when a game is started or a valid player is activated.
    ///
    /// \param currentBoard The changed board.
    void sigCheckerBoardChanged(GamePlay::CheckerBoard currentBoard);

private:
    GamePlay m_gamePlay;
    VirtualPlayer *m_playerBlack;
    VirtualPlayer *m_playerWhile;

    void cleanup();
    void gamePlayCheckerBoardChangedHandler(GamePlay::CheckerBoard currentBoard);
    void gamePlayPlayerChangedHandler(PlayerColor playerColor);
    void gamePlayGameOverHandler(PlayerColor winner);
};

#endif // ROUND_H
