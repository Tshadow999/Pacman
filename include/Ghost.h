#pragma once

// These two are for random.
#include <cstdlib>
#include <ctime>

#include "GameObjectStruct.h"
#include "GameManager.h"

struct GhostStruct : GameObjectStruct {

	GhostStruct(int x, int y, Type ghost) : GameObjectStruct{ x,y, ghost, UP } {
		std::srand(time(0)); // Initialize with a random seed
	};
	GhostStruct(Point2D poisition, Type ghost) : GameObjectStruct{ poisition.x, poisition.y, ghost, UP } {
		std::srand(time(0)); // Initialize with a random seed
	};

	/// <summary>
	/// Make the ghost scared for a certain amount of ticks
	/// </summary>
	void TurnScared() {
		if (_isScared) return;

		type = SCARED;

		_isScared = true;
		_scaredCounter = 0;
	}

	/// <summary>
	/// This method should be called in every update frame.
	/// </summary>
	void Tick() {
		// Make ghosts move slower.
		HandleScaredState();

		_readyToMove = !_readyToMove;

		if (_canMove && _readyToMove) {
			Move();
		}
		else {
			if (_waitingCounter++ >= WAIT_TO_MOVE_TICKS) {
				_canMove = true;
				_waitingCounter = 0;
			}
		}

		Eat();
	}

protected:
	// This handles for how long a ghost is scared
	short _scaredCounter{ 0 };
	const short MAX_SCARED_TICKS = 75;
	bool _isScared{ false };

	// How many ticks before the ghosts start moving after reset / initially
	short _waitingCounter{ 0 };
	const short WAIT_TO_MOVE_TICKS = 45;
	bool _readyToMove{ false };

	const int RANDOM_MOVE_CHANCE{ 15 }; // 15 % chance to move randomly

	void Eat() {
		// Do not eat when scared
		if (_isScared) return;

		Point2D currentPosition(x, y);


		GameManager::Get().TryEatPacman(currentPosition);
	}

	void HandleScaredState() {
		if (!_isScared) return;
		_scaredCounter++;
		// Ghost is no longer scared
		if (_scaredCounter >= MAX_SCARED_TICKS) {
			_isScared = false;
			type = _initialType;
			GameManager::Get().GetPacman()->ToggleGhostEating(false);
		}
	}

	// Make each Ghost be able to have different Move patterns using the definition below:
	// virtual void Move() = 0;

	// For now, each ghost has the same movement patterns, but due to random, should be different
	void Move() {
		GameManager& manager = GameManager::Get();

		Direction originalDir = dir;

		Point2D nextPosition = GetNextPosition();

		int doRandomMovement = rand() % 100; // Make choice out of 100 options (0 to 99)
		int randomDir = rand() % 4; // 4 directions

		std::vector<Point2D> possilePaths = { UpDir(), DownDir(), LeftDir(),  RightDir() };

		// Keep moving in the current direction
		if (manager.CanMove(nextPosition) && (doRandomMovement >= RANDOM_MOVE_CHANCE)) {
			x = nextPosition.x;
			y = nextPosition.y;
			return;
		}

		if (manager.CanMove(possilePaths[randomDir])) {
			// Check if we can move in the random direction
			dir = (Direction)randomDir;

			x = possilePaths[randomDir].x;
			y = possilePaths[randomDir].y;

			return;
		}

		// We either cannot move in the current direction or we cannot move in the random direction
		for (int i = 0; i < 4; i++) {
			if (manager.CanMove(possilePaths[i])) {
				dir = (Direction)i;

				x = possilePaths[i].x;
				y = possilePaths[i].y;
				return;
			}
		}
	}

};

struct ClydeGhost : GhostStruct {
	ClydeGhost(int x, int y) : GhostStruct{ x,y, CLYDE } {};
	ClydeGhost(Point2D position) : GhostStruct{ position.x, position.y, CLYDE } {};
};

struct PinkyGhost : GhostStruct {
	PinkyGhost(int x, int y) : GhostStruct{ x,y, PINKY } {};
	PinkyGhost(Point2D position) : GhostStruct{ position.x, position.y, PINKY } {};
};

struct BlinkyGhost : GhostStruct {
	BlinkyGhost(int x, int y) : GhostStruct{ x,y, BLINKY } {};
	BlinkyGhost(Point2D position) : GhostStruct{ position.x, position.y, BLINKY } {};
};

struct InkyGhost : GhostStruct {
	InkyGhost(int x, int y) : GhostStruct{ x,y, INKY } {};
	InkyGhost(Point2D position) : GhostStruct{ position.x, position.y, INKY } {};
};