#pragma once

#include <vector>
#include <iostream>
#include "Point2D.h"
#include "Collidable.h"

class GameManager
{
public:
    // Get a reference to the GameManager
    static GameManager& Get(); 

    // For a Singleton to work we do not want to have a "copy constructor", so we delete it.
    // this dissalowes other classes to do  : GameManager instance = GameManager.GetInstance(); 
    // but requires them to to this         : GameManager& instance = GameManager.GetInstance(); 
    // Thus no instance is copied.
    GameManager(const GameManager&) = delete;
    // Also delete the assignment operator, since this is good practise, when dealing with singletons.
    GameManager& operator = (const GameManager&) = delete;

#pragma region Board
    std::vector<std::vector<short>>& GetBoard();

    void PrintBoard();

    short GetValueAt(Point2D position);
    void SetValueAt(Point2D position, short value);

#pragma endregion

#pragma region Movement
    bool CanMove(Point2D& position);

#pragma endregion

#pragma region Lives
    void ReduceLives();
    short GetLives();
#pragma endregion

#pragma region Score
    void AddScore(int amountToAdd);
    int GetScore();
#pragma endregion

    // PacmanStruct GetPacman();

private:
    const static short BOARD_COLUMNS = 28;
    const static short BOARD_ROWS = 27; 

    // Starting position
    // PacmanStruct _pacman{ 13, 11, UP };

    short _lives{ 3 };
    int _score{ 0 };
    int _dotCount{0};
    bool _levelCompleted{ false };

    std::vector<std::vector<short>> _gameBoard = { {
        #include "board.def"
    } };

    GameManager() {};

    bool IsValidPosition(Point2D position);
    bool IsValidPosition(int x, int y);
};