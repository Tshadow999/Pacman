#include "GameManager.h"

/// <summary>
/// Creates a static instance of the GameManager if it did not exist already.
/// </summary>
/// <returns>GameManager instance</returns>
GameManager& GameManager::Get() {
    static GameManager instance;
    return instance;
}

/// <summary>
/// Prints the game board to the console
/// For debugging purposes
/// </summary>
void GameManager::PrintBoard() {
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLUMNS; col++) {
            std::cout << _gameBoard[row][col] << " ";
            if (_gameBoard[row][col] < 10) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

/// <param name="position">to check the value</param>
/// <returns>the value in the gameboard at the position</returns>
short GameManager::GetValueAt(Point2D position)
{
    if (!IsValidPosition(position)) return -1;
     
    // Reverse x and y, since that is how the position and array indexing work
    return _gameBoard[position.y][position.x];
}

/// <summary>
/// Sets the value of a position in the gameboard
/// </summary>
/// <param name="position"></param>
/// <param name="value"></param>
void GameManager::SetValueAt(Point2D position, short value) {
    if (!IsValidPosition(position)) return;

    // Dot is going to be eaten.
    if (_gameBoard[position.y][position.x] == Dot && value == 0) {
        _dotCount--;
        AddScore(SCORE_DOT);
    }

    // Reverse x and y, since that is how the position and array indexing work
    _gameBoard[position.y][position.x] = value;

    // All dots are eaten, level is now completed
    if (_dotCount == 0) {
        _levelCompleted = true;
        std::cout << "Well done!\nYou have completed this level of pacman.\n";
    }
}

/// <summary>
/// Checks if one can move to the position
/// </summary>
/// <param name="position">to check. Will be modified if </param>
/// <returns>True if there is no wall at the position</returns>
bool GameManager::CanMove(Point2D& position) {

    // Check the portal. (0, 13), (27, 13)
    if (position.x < 0 && position.y == 13) {
        position.x = BOARD_ROWS;
        return true;
    }
    else if (position.x > BOARD_ROWS && position.y == 13) {
        position.x = 0;
        return true;
    }

    // Check for out of bounds.
    if (!IsValidPosition(position)) return false;

    // Reverse x and y, since that is how the position and array indexing work
    return _gameBoard[position.y][position.x] != 1;
}

/// <summary>
/// Statically gets the game board so the instance in not required
/// </summary>
/// <returns>The game board</returns>
std::vector<std::vector<short>>& GameManager::GetBoard() { return _gameBoard; }

/// <summary>
/// Will reduce pacmans live by one. When there are no more lives, the game is over.
/// </summary>
void GameManager::ReduceLives() {
    // Reduces amount of lives
    if (--_lives <= 0) {
        // Game over, just quit?
        //TODO
    }
}

/// <returns>The amount of lives pacman has</returns>
short GameManager::GetLives() { return _lives; }

/// <param name="position"> to check</param>
/// <returns>true if valid, false if not valid</returns>
bool GameManager::IsValidPosition(Point2D position) { return IsValidPosition(position.x, position.y); }


/// <param name="x">part of the point</param>
/// <param name="y">part of the point</param>
/// <returns>true if valid, false if not valid</returns>
bool GameManager::IsValidPosition(int x, int y) {
    // x and or y are too small
    if (x < 0 || y < 0) return false;

    // x and or y are too big
    if (x >= BOARD_COLUMNS || y >= BOARD_ROWS) return false;

    return true;
}

/// <returns>The score pacman currently has</returns>
int GameManager::GetScore() { return _score; }

/// <returns>true if the all dots have been eaten</returns>
bool GameManager::IsLevelCompleted() { return _levelCompleted; }


/// <summary>
/// Adds an amount to the score variable
/// </summary>
/// <param name="amountToAdd">should be positive</param>
void GameManager::AddScore(int amountToAdd) { _score += amountToAdd; }

/// <summary>
/// Use SetPacman before calling this method
/// </summary>
/// <returns>a pointer to the pacman object</returns>
PacmanStruct* GameManager::GetPacman()
{
    // We have not yet recieved a pacman
    if (_pacman == nullptr) {
        std::cout << "Pacman is still null at this point!\n";
        std::cout << "Please initialize pacman with the SetPacman method\n\n";
        return nullptr;
    }
    return _pacman;
}
/// <summary>
/// Sets the pacman instance so others can get access to it.
/// </summary>
/// <param name="pacman">the pacman</param>
void GameManager::SetPacman(PacmanStruct* pacman)
{
}
