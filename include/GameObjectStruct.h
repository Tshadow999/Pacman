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
enum Direction { UP, DOWN, LEFT, RIGHT };

/// This represents an item that is drawn onto the screen.
struct GameObjectStruct {
    /// x-position of the item.
    int x;
    /// y-position of the item.
    int y;
    /// The appearance of the item (sprite set).
    Type type;
    /// The direction of the item (sprite selection).
    Direction dir;

    /// <returns>the next position using the current direction</returns>
    Point2D GetNextPosition()
    {
        // Since top left is (0,0) up: y - 1; down: y + 1; left: x - 1; right: x + 1;
        switch (dir) {
        case UP:
            return Point2D(x, y - 1);
        case DOWN:
            return Point2D(x, y + 1);
        case LEFT:
            return Point2D(x - 1, y);
        case RIGHT:
            return Point2D(x + 1, y);
        default:
            // Should never get here
            return Point2D(0, 0);
        }
    }
};