#pragma once

// These two are for random.
#include <cstdlib>
#include <ctime>

#include <vector>
#include <iostream>

#include "Point2D.h"
#include "Collidable.h"

typedef struct PacmanStruct;
typedef struct GhostStruct;

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
    std::vector<std::vector<short>>* GetBoard();

    void PrintBoard();

    short GetValueAt(Point2D position);
    void SetValueAt(Point2D position, short value);
    void SpawnFruit();

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

#pragma region Ghosts

     void AddGhost(GhostStruct* ghost) {
         _ghosts.push_back(ghost);
     }

     void TryEatGhost(Point2D pacmanPos);

#pragma endregion

private:
    const static short BOARD_COLUMNS = 28;
    const static short BOARD_ROWS = 27; 

#pragma region ScoreValues
    const int SCORE_DOT = 10;
    const int SCORE_ENERGIZER = 50;

    // All Fruit have different score values, 
    // For simplicity just add the same value for each of the fruits (orange == 500)
    const int SCORE_FRUIT = 500;

    // Spawn 3 fruits over the game
    int _fruitFirstSpawnScore {  750 };
    int _fruitSecondSpawnScore{ 3500 };
    int _fruitThirdSpawnScore { 7500 };

    // To make fruit spawn just once.
    bool _fruitFirstHasSpawned{ false };
    bool _fruitSecondHasSpawned{ false };
    bool _fruitThirdHasSpawned{ false };

    // Eat multiple ghosts and recieve double for each one you eat.
    const int SCORE_GHOST = 200; 
    int _scoreGhostMultiplier = 1;

#pragma endregion

    // Starting position
    PacmanStruct* _pacman{ nullptr };
    std::vector<GhostStruct*> _ghosts;

    short _lives{ 3 };
    int _score{ 0 };
    int _dotCount{264};
    bool _levelCompleted{ false };

    std::vector<std::vector<short>> _gameBoard = { {
        #include "board.def" 
    } };

    GameManager() {
        // Get random seed
        std::srand(time(0));
    };

    bool IsValidPosition(Point2D position);
    bool IsValidPosition(int x, int y);

    // Only the game manager should be able to change the score
    void AddScore(int amountToAdd);
};