#pragma once

#include "Point2D.h"

/// These enum values denote the sprite sets available for items on screen.
enum Type {
    PACMAN,
    BLINKY,
    PINKY,
    INKY,
    CLYDE,
    SCARED,
    SCAREDINV,
    CHERRY,
    STRAWBERRY,
    ORANGE,
    LEMON,
    APPLE,
    GRAPES,
    DOT,
    ENERGIZER,
    WALL,
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE
};

/// An enum to denote the direction of an item on screen.
enum Direction { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

/// This represents an item that is drawn onto the screen.
struct GameObjectStruct {

    GameObjectStruct(int x, int y, Type type, Direction dir) : x{ x }, y{ y }, type{ type }, dir{ dir } {
        _initialX = x;
        _initialY = y;
        _initialDir = dir;
        _initialType = type;
    };

    int x;
    int y;

    Type type;
    
    Direction dir;

    Point2D UpDir() { return Point2D(x, y - 1); }
    Point2D DownDir() { return Point2D(x, y + 1); }
    Point2D LeftDir() { return Point2D(x - 1, y ); }
    Point2D RightDir() { return Point2D(x + 1, y); }

    /// <returns>the next position using the current direction</returns>
    Point2D GetNextPosition()
    {
        // Since top left is (0,0) up: y - 1; down: y + 1; left: x - 1; right: x + 1;
        switch (dir) {
        case UP:
            return UpDir();
        case DOWN:
            return DownDir();
        case LEFT:
            return LeftDir();
        case RIGHT:
            return RightDir();
        default:
            // Should never get here
            return Point2D(0, 0);
        }
    }
    /// <summary>
    /// Resets the gameObjects to the initial position
    /// </summary>
    void Reset() {
        x = _initialX;
        y = _initialY;
        dir = _initialDir;
        type = _initialType;
    }
    /// <summary>
    /// Toggles the movement of the ghosts
    /// </summary>
    /// <param name="toggle">: true for movement, false for no movement</param>
    void ToggleMovement(bool toggle) {
        _canMove = toggle;
    }

private:
    int _initialX;
    int _initialY;
    Type _initialType;
    Direction _initialDir;

protected:
    bool _canMove{ false };
};