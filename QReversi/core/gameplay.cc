#include "gameplay.h"

GamePlay::GamePlay(QObject *parent)
    : QObject(parent)
{
    reset();
}

bool GamePlay::isMoveable(GamePlay::Position pos)
{
    if (tryMove(pos, m_currentPlayer, false) > 0)
    {
        return true;
    }
    return false;
}

void GamePlay::slotStartNewGame()
{
    reset();
    m_running = true;
    m_currentPlayer = Black;
    emit sigCheckerBoardChanged(m_board);
    emit sigPlayerChanged(m_currentPlayer);
}

void GamePlay::slotMove(GamePlay::Position pos)
{
    if (!m_running) return;
    if (m_currentPlayer == Unknown) return;
    if (tryMove(pos, m_currentPlayer, true) > 0)
    {
        emit sigCheckerBoardChanged(m_board);
        // Determine if the sub-party has changed
        PlayerColor nextPlayer = (m_currentPlayer == Black) ? White : Black;
        if (playerCanMove(nextPlayer))
        {
            m_currentPlayer = nextPlayer;
            emit sigPlayerChanged(m_currentPlayer);
            return;
        }
        if (!playerCanMove(nextPlayer) && playerCanMove(m_currentPlayer))
        {
            emit sigPlayerChanged(m_currentPlayer);
            return;
        }
        if (!playerCanMove(nextPlayer) && !playerCanMove(m_currentPlayer))
        {
            // No player can continue to play, the game is over, send a signal.
            PlayerColor winner = getWinner();
            emit sigGameOver(winner);
            m_running = false;
            return;
        }
    }
}

size_t GamePlay::tryMove(GamePlay::Position pos, PlayerColor playerColor, bool realMove)
{
    std::array<std::array<int, 2>, 8> directions =
    {
        {
            {-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
            {0, 1},   {1, -1}, {1, 0},  {1, 1}
        }
    }; // Eight directions

    if (pos.row >= kBoardRows || pos.col >= kBoardColumns)
        return 0;
    if (m_board[pos.row][pos.col] != Unknown)
        return 0;

    PlayerColor self = playerColor;
    PlayerColor opponent = self == Black ? White : Black;

    size_t count = 0;

    // Traverse 8 directions to see if you can eat each other's pieces
    for (std::array<int, 2> direction : directions)
    {
        size_t row = pos.row;
        size_t col = pos.col;
        // Extend in direction
        row += direction[0];
        col += direction[1];
        size_t steps = 1; // Extended steps
        while (row < kBoardRows && col < kBoardColumns && m_board[row][col] == opponent)
        {
            row += direction[0];
            col += direction[1];
            ++steps;
        }
        // Has reached the end of the extension

        if (steps < 2)
            continue; // The number of steps is less than 2, there is no opponent in the middle

        // Look at the end points is not your own pieces
        if (row < kBoardRows && col < kBoardColumns && m_board[row][col] == self)
        {
            row -= direction[0];
            col -= direction[1];
            --steps;
            // Reverse the extension to flip the opponent's piece in the middle
            while (steps != 0)
            {
                if (realMove)
                {
                    m_board[row][col] = self; // Flip the piece
                }
                row -= direction[0];
                col -= direction[1];
                --steps;
                ++count; // Flip the opponent's number of pieces plus one
            }
        }
    }

    if (count > 0 && realMove) // keep eye on realMove!
    {
        m_board[pos.row][pos.col] = self;
    }

    return count;
}

bool GamePlay::playerCanMove(GamePlay::PlayerColor playerColor)
{
    for (size_t row = 0; row != kBoardRows; ++row)
    {
        for (size_t col = 0; col != kBoardColumns; ++col)
        {
            if (tryMove({row, col}, playerColor, false) > 0)
            {
                return true;
            }
        }
    }
    return false;
}

GamePlay::PlayerColor GamePlay::getWinner()
{
    size_t numOfBlack = 0;
    size_t numOfWhite = 0;
    for (const auto& row : m_board)
    {
        for (const auto& playerColor : row)
        {
            if (playerColor == Black)
            {
                ++numOfBlack;
            }
            if (playerColor == White)
            {
                ++numOfWhite;
            }
        }
    }

    if (numOfBlack > numOfWhite)
        return Black;
    else if (numOfBlack < numOfWhite)
        return White;
    else
        return Unknown;
}

void GamePlay::reset()
{
    for(size_t i = 0; i < kBoardRows; i++)
    {
        for(size_t j = 0; j < kBoardColumns; j++)
        {
            m_board[i][j] = Unknown;
        }
    }
    m_board[3][3] = m_board[4][4] = White;
    m_board[3][4] = m_board[4][3] = Black;
    m_running = false;
    m_currentPlayer = Unknown;
    emit sigCheckerBoardChanged(m_board);
}
