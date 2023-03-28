#pragma once

#include "GameObjectStruct.h"
#include "GameManager.h"
#include "Point2D.h"


struct GhostStruct : GameObjectStruct {

	GhostStruct(int x, int y, Type ghost) : GameObjectStruct{ x,y, ghost, UP } {};
GhostStruct(Point2D poisition, Type ghost) : GameObjectStruct{ poisition.x, poisition.y, ghost, UP } {};

/// <summary>
/// Make the ghost scared for a certain amount of ticks
/// </summary>
void TurnScared() {
	if (_isScared) return;

	_isScared = true;
	_scaredCounter = 0;
}

/// <summary>
/// This method should be called in every update frame.
/// </summary>
void Tick() {
	HandleScaredState();
	Move();
	Eat();
}
protected:
	int _randomDir{ 0 };

	// This handles for how long a ghost is scared
	short _scaredCounter{ 0 };
	const short MAX_SCARED_TICKS = 30;
	bool _isScared{ false };

	// Make each Ghost be able to have different Move patterns
	virtual void Move() = 0;

	void Eat() {
		Point2D currentPosition(x, y);

		GameManager::Get().TryEatPacman(currentPosition);
	}

	void IncreaseRandomDirection() {
		// we have four directions thus Modulo 4
		_randomDir = ((_randomDir + 1) % 4);
	}

	void HandleScaredState() {
		if (!_isScared) return;
		_scaredCounter++;
		type = SCARED;
		// Ghost is no longer scared
		if (_scaredCounter >= MAX_SCARED_TICKS) {
			_isScared = false;
		}
	}

};

struct ClydeGhost : GhostStruct {

	ClydeGhost(int x, int y) : GhostStruct{ x,y, CLYDE } {};
	ClydeGhost(Point2D position) : GhostStruct{ position.x, position.y, CLYDE } {};

	void Move() {

	}
};

struct PinkyGhost : GhostStruct {

	PinkyGhost(int x, int y) : GhostStruct{ x,y, PINKY } {};
	PinkyGhost(Point2D position) : GhostStruct{ position.x, position.y, PINKY } {};

	void Move() {

	}
};

struct BlinkyGhost : GhostStruct {

	BlinkyGhost(int x, int y) : GhostStruct{ x,y, BLINKY } {};
	BlinkyGhost(Point2D position) : GhostStruct{ position.x, position.y, BLINKY } {};

	void Move() {
		GameManager& manager = GameManager::Get();

		Direction originalDir = dir;

		Point2D nextPosition = GetNextPosition();

		std::vector<Point2D> possilePaths = { UpDir(), DownDir(), LeftDir(),  RightDir() };

		// Keep moving in the current direction
		if (manager.CanMove(nextPosition)) {
			x = nextPosition.x;
			y = nextPosition.y;
			return;
		}

	}
};

struct InkyGhost : GhostStruct {

	InkyGhost(int x, int y) : GhostStruct{ x,y, INKY } {};
	InkyGhost(Point2D position) : GhostStruct{ position.x, position.y, INKY } {};

	void Move() {

	}
};