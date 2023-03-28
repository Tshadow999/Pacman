#pragma once

#include <vector>
#include <iostream>
#include "Point2D.h"
#include "Collidable.h"
#include "GameObjectStruct.h"

struct PacmanStruct;

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
    std::vector<std::vector<short>> GetBoard();

    void PrintBoard();

    short GetValueAt(Point2D position);
    void SetValueAt(Point2D position, short value);

#pragma endregion

#pragma region Movement
    bool CanMove(Point2D& position);
#pragma endregion

    void Reset();

#pragma region Lives
    void ReduceLives();
    short GetLives();
#pragma endregion

#pragma region Score
    int GetScore();
    bool IsLevelCompleted();
#pragma endregion

#pragma region Pacman
     PacmanStruct* GetPacman();
     void SetPacman(PacmanStruct* pacman);
     void TryEatPacman(Point2D positionToCheck);
#pragma endregion

     void AddGhost(GameObjectStruct ghost) {
         _ghosts.push_back(ghost);
     }

private:
    const static short BOARD_COLUMNS = 28;
    const static short BOARD_ROWS = 27; 

#pragma region ScoreValues
    const int SCORE_DOT = 10;
    const int SCORE_ENERGIZER = 50;

    // All Fruit have different score values, 
    // For simplicity just add the same value for each of the fruits (orange == 500)
    const int SCORE_FRUIT = 500;

    const int SCORE_GHOST = 200; // Eat multiple ghosts and recieve double for each one you eat.
#pragma endregion

    // Starting position
    PacmanStruct* _pacman{ nullptr };
    std::vector<GameObjectStruct> _ghosts;

    short _lives{ 3 };
    int _score{ 0 };
    int _dotCount{268};
    int _ghostsEaten{ 0 };
    bool _levelCompleted{ false };

    std::vector<std::vector<short>> _gameBoard = { {
        #include "board.def" 
    } };

    GameManager() {};

    bool IsValidPosition(Point2D position);
    bool IsValidPosition(int x, int y);

    // Only the game manager should be able to change the score
    void AddScore(int amountToAdd);

};