#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>

#include <array>


/// \brief The Othello gameplay class defines the external interface of the game core.
///
/// This class defines the game character, the board, the board position, and the gameplay.
///
/// Through this class, you can create a new game, play it on the board.
///
/// Each time the child is sent, the next child will change the signal (there may be no actual change when one party continues to play).
/// A game end signal is issued at the end of the game.
///
/// According to the rule of Othello, each new game is Black.
class GamePlay : public QObject
{
    Q_OBJECT

public:
    static const size_t kBoardRows = 8; ///< The number of checkerboard lines.
    static const size_t kBoardColumns = 8; ///< The number of chessboards.

    /// \brief The next child color.
    enum PlayerColor {
        Black,
        White,
        Unknown
    };
    /// \brief The position on the board.
    struct Position {
        size_t row; ///< Row
        size_t col; ///< Column
    };
    /// \brief checkerboard.
    using CheckerBoard = std::array<std::array<PlayerColor, kBoardColumns>, kBoardRows>;

    /// \brief Constructor.
    explicit GamePlay(QObject *parent);

    /// \brief Determine if a position can be played.
    /// \param pos Lower position.
    /// \return Whether it is possible to play.
    bool isMoveable(Position pos);
    /// \brief Get the current board.
    /// \return The current board.
    CheckerBoard getCheckerBoard();
    /// \brief Check if the game is in progress.
    /// \return True is in progress, false is vice versa.
    bool isRunning();
    /// \brief Get the current lower child.
    /// \return The current sub-party.
    PlayerColor getCurrentPlayerColor();

public slots:
    /// \brief Start a new game.
    void slotStartNewGame();
    /// \brief Under the child.
    ///
    /// Note: When you are in a position, you do not need to specify the next child. The next child is determined every time you play.
    ///
    /// \param pos Lower position.
    void slotMove(Position pos);

    /// \brief Reset.
    void reset();

signals:
    /// \brief The board changes the signal.
    ///
    /// This signal is sent when the board changes. This signal is sent when a game is started or a valid player is activated.
    ///
    /// \param currentBoard The changed board.
    void sigCheckerBoardChanged(CheckerBoard currentBoard);
    /// \brief The next sub-party changes the signal.
    /// \param playerColor is currently in the sub-party, and the game is Unknown when it is not started or ended.
    void sigPlayerChanged(PlayerColor playerColor);
    /// \brief The game ends with a multiple.
    /// \param playerColor Winner, the draw is Unknown.
    void sigGameOver(PlayerColor playerColor);

private:
    CheckerBoard m_board; ///< The current board.
    bool m_running; ///< Whether the game is in progress.
    PlayerColor m_currentPlayer; ///< Currently the next player.

    /// \brief Try it in one place.
    ///
    /// This function can be used to test whether a position can be subscripted. It will return the hypothesis that it is flipped after a given position.
    /// The number of the opponent's pieces, and the \p realMove parameter can be used to determine whether or not the player is actually on the board.
    ///
    /// \param pos Lower position.
    /// \param playerColor The color of the next child.
    /// \param realMove is false. It is not actual. When it is true, it is actually down.
    /// \return The next child flips the number of opponents after the specified position.
    size_t tryMove(Position pos, PlayerColor playerColor, bool realMove);
    /// \brief Determine if a player can play.
    /// \param playerColor The player who wants to go down.
    /// \return If true, the specified player can be moved, false otherwise.
    bool playerCanMove(PlayerColor playerColor);

    PlayerColor getWinner();

    friend class Ai;
};

inline GamePlay::CheckerBoard GamePlay::getCheckerBoard()
{
    return m_board;
}

inline bool GamePlay::isRunning()
{
    return m_running;
}

inline GamePlay::PlayerColor GamePlay::getCurrentPlayerColor()
{
    return m_currentPlayer;
}

#endif // GAMEMODEL_H
